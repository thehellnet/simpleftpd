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

#ifndef __SIMPLEFTPD_STACK_H
#define __SIMPLEFTPD_STACK_H

#include <pthread.h>

struct stack_item_t {
    unsigned long long id;
    pthread_t *pthread;
    struct stack_item_t *next;
    struct stack_item_t *prev;
};

typedef struct stack_item_t stack_item;

void stack_init();

stack_item *stack_add();

void stack_remove(stack_item *stack);

stack_item *stack_first();

int stack_count();

void stack_free(stack_item *stack);

#endif
