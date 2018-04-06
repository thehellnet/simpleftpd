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

#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <errno.h>
#include <memory.h>
#include <signal.h>

#include "simpleftpd.h"
#include "config.h"
#include "socket.h"
#include "ui.h"
#include "worker.h"

static const char *tag = "main";

char *program_name;
cfg *config;
int keep_running;

int sock;

int main(int argc, char **argv) {
    int result;
    int new_sock;
    struct sockaddr_in address;
    size_t address_len;

    stack_item *old_stack;
    stack_item *stack;
    worker_data *data;

    program_name = argv[0];

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    cfg_init();
    result = cfg_parse_command_line(argc, argv);
    cfg_print();

    if (!result)
        return EXIT_FAILURE;

    sock = sck_init();
    sck_listen(sock);

    stack_init();

    keep_running = 1;
    while (keep_running == 1) {
        ui_message(UI_INFO, tag, "Accepting new connections");

        new_sock = accept(sock, (struct sockaddr *) &address, (socklen_t *) &address_len);
        if (new_sock == -1) {
            if (errno == EBADF) {
                ui_message(UI_INFO, tag, "Socket closed, no accepting new socket connections.");
                break;
            }

            ui_message(UI_ERROR, tag, "Unable to accept new socket connection. Error %d: %s", errno, strerror(errno));
            return EXIT_FAILURE;
        }

        stack = stack_add();

        data = (worker_data *) malloc(sizeof(worker_data));
        data->sock = new_sock;
        data->address = address;
        data->address_len = address_len;
        data->stack = stack;

        pthread_create(stack->pthread, NULL, thread_function, data);
    }

    stack = stack_first();
    while (stack != NULL) {
        ui_message(UI_INFO, tag, "Joining worker %d", stack->id);

        pthread_join(*stack->pthread, NULL);

        old_stack = stack;
        stack = stack->next;

        stack_remove(old_stack);
    }

    return EXIT_SUCCESS;
}

void signal_handler(int signal) {
    switch (signal) {
        case SIGINT:
        case SIGTERM:
            keep_running = 0;
            sck_close(sock);
            break;

        default:
            break;
    }
}

void *thread_function(void *thread_data) {
    worker_data *data;

    data = (worker_data *) thread_data;

    worker_main(data);

    stack_remove(data->stack);

    ui_message(UI_INFO, tag, "Worker removed from stack. Remaining %d workers.", stack_count());

    free(data);

    return NULL;
}