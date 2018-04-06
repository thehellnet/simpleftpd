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
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include "socket.h"
#include "ui.h"

static const char *tag = "sck";

extern cfg *config;

int sck_init() {
    int result;
    int sck;
    int opt;

    ui_message(UI_INFO, tag, "Creating socket");
    sck = socket(AF_INET, SOCK_STREAM, 0);
    if (sck == 0) {
        ui_message(UI_ERROR, tag, "Unable to create socket. Error code: %d", errno);
        return 0;
    }

    ui_message(UI_INFO, tag, "Setting socket options");
    opt = 1;
    result = setsockopt(sck, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (result != 0) {
        ui_message(UI_ERROR, tag, "Unable to create socket. Error code: %d", errno);
        return 0;
    }

    return sck;
}

int sck_listen(int sck) {
    int result;
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(config->tcp_port);

    ui_message(UI_INFO, tag, "Binding socket to address and port");
    result = bind(sck, (struct sockaddr *) &address, sizeof(address));
    if (result == -1) {
        ui_message(UI_ERROR, tag, "Unable to create socket. Error code: %d", errno);
        return 0;
    }

    ui_message(UI_INFO, tag, "Put socket in listen mode");
    result = listen(sck, config->tcp_max_connections);
    if (result == -1) {
        ui_message(UI_ERROR, tag, "Unable to put socket in listen mode. Error code: %d", errno);
        return 0;
    }

    return 1;
}

void sck_close(int sck) {
    ui_message(UI_INFO, tag, "Closing socket");
    close(sck);
}