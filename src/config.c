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

#include <stdio.h>
#include <malloc.h>
#include <getopt.h>
#include <stdlib.h>
#include <memory.h>

#include "config.h"
#include "default.h"
#include "ui.h"

static const char *tag = "cfg";

static char *options_short = "p:";

static struct option options_long[] = {
        {"tcp-port", required_argument, 0, 'p'},
        {0, 0,                          0, 0}
};

extern cfg *config;

void cfg_init() {
    config = (struct cfg_t *) malloc(sizeof(struct cfg_t));

    config->debug_level = SIMPLEFTPD_DEFAULT_CONFIG_DEBUG_LEVEL;
    config->tcp_port = SIMPLEFTPD_DEFAULT_CONFIG_TCP_PORT;
    config->tcp_max_connections = SIMPLEFTPD_DEFAULT_CONFIG_TCP_MAX_CONNECTIONS;
}

void cfg_free() {
    free(config);
}

int cfg_parse_command_line(int argc, char **argv) {
    int ret;

    int option_index;
    int c;

    ret = 1;
    option_index = 0;

    while (1) {
        c = getopt_long(argc, argv, options_short, options_long, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 'p':
                config->tcp_port = (uint16_t) strtoul(optarg, 0, 0);
                break;

            default:
                ret = 0;
                break;
        }
    }

    return ret;
}

void cfg_print() {
    char buff[128];

    memset(buff, '\0', sizeof(buff));
    switch (config->debug_level) {
        case UI_DISABLE:
            sprintf(buff, "DISABLE");
            break;
        case UI_ERROR:
            sprintf(buff, "ERROR");
            break;
        case UI_WARNING:
            sprintf(buff, "WARNING");
            break;
        case UI_INFO:
            sprintf(buff, "INFO");
            break;
        case UI_DEBUG:
            sprintf(buff, "DEBUG");
            break;
        default:
            break;
    }
    ui_message(UI_INFO, tag, "debug-level = %d %s", config->debug_level, buff);

    ui_message(UI_INFO, tag, "tcp-port = %d", config->tcp_port);
}
