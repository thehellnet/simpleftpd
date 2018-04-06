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

#ifndef __SIMPLEFTPD_CONFIG_H
#define __SIMPLEFTPD_CONFIG_H

#include <stdint.h>

struct cfg_t {
    int debug_level;

    uint16_t tcp_port;
    uint16_t tcp_max_connections;
};

typedef struct cfg_t cfg;

void cfg_init();

void cfg_free();

int cfg_parse_command_line(int argc, char **argv);

void cfg_print();

#endif
