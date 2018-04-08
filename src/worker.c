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

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "worker.h"
#include "ui.h"
#include "libsimpleftp/context.h"
#include "libsimpleftp/command.h"

static const char *tag = "worker";

void worker_main(worker_data *data) {
    char c;
    ssize_t ln;
    char buffer[4096];
    simpleftp_context *context;


    ui_message(UI_INFO, tag, "Starting worker %d for %s", data->stack->id, inet_ntoa(data->address.sin_addr));

    ui_message(UI_DEBUG, tag, "Init context", data->stack->id);
    context = NULL;
    simpleftp_context_init(context);

    simpleftp_response_success_connection_ready(buffer, context);
    worker_socket_write(data->sock, buffer);

    while (1) {
        ln = read(data->sock, &c, 1);
        if (ln != 1)
            break;

        ui_message(UI_DEBUG, tag, "Read a byte from worker %d", data->stack->id);
    }

    ui_message(UI_DEBUG, tag, "Freeing context", data->stack->id);
    simpleftp_context_free(context);

    ui_message(UI_INFO, tag, "Closing socket for worker %d", data->stack->id);
    close(data->sock);

    ui_message(UI_INFO, tag, "Worker %d finished", data->stack->id);
}

void worker_socket_write(int socket, char *data) {
    strcat(data, "\n");
    write(socket, data, strlen(data));
}