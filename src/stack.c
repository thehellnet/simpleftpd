/*
 * SimpleFTPd
 * Copyright (C) 2018  Luca Cireddu
 * sardylan@gmail.com
 * https://www.lucacireddu.it
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <malloc.h>

#include "stack.h"

unsigned long long next_id;
stack_item *first;
stack_item *last;
pthread_mutex_t stack_mutex;

void stack_init() {
    pthread_mutex_lock(&stack_mutex);

    next_id = 0;

    first = NULL;
    last = NULL;

    pthread_mutex_unlock(&stack_mutex);
}

stack_item *stack_add() {
    stack_item *prev;
    pthread_mutex_lock(&stack_mutex);

    prev = NULL;

    if (last == NULL) {
        last = (stack_item *) malloc(sizeof(stack_item));
        first = last;
    } else {
        prev = last;
        last->next = (stack_item *) malloc(sizeof(stack_item));
        last = last->next;
    }

    last->id = next_id;
    last->next = NULL;
    last->prev = prev;
    last->pthread = (pthread_t *) malloc(sizeof(pthread_t));

    next_id++;

    pthread_mutex_unlock(&stack_mutex);

    return last;
}

void stack_remove(stack_item *stack) {
    stack_item *next;
    stack_item *prev;

    pthread_mutex_lock(&stack_mutex);

    if (stack == NULL)
        return;

    next = stack->next;
    prev = stack->prev;

    if (next != NULL)
        next->prev = prev;
    else
        last = prev;

    if (prev != NULL)
        prev->next = next;
    else
        first = next;

    stack_free(stack);

    pthread_mutex_unlock(&stack_mutex);
}

stack_item *stack_first() {
    return first;
}

int stack_count() {
    int count;
    stack_item *item;

    pthread_mutex_lock(&stack_mutex);

    count = 0;
    item = first;
    while (item != NULL) {
        count++;
        item = item->next;
    }

    pthread_mutex_unlock(&stack_mutex);

    return count;
}

void stack_free(stack_item *stack) {
    free(stack->pthread);

    free(stack);
}
