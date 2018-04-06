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
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include "version.h"
#include "config.h"
#include "ui.h"
#include "default.h"

extern cfg *config;
extern const char *program_name;

void ui_usage() {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    %s [<option> <value> ...]\n", program_name);
}

void ui_version() {
    fprintf(stderr, "Corelink %s\n", APPLICATION_VERSION);
}

void ui_help() {
    ui_version();
    fprintf(stderr, "\n");

    ui_usage();

    fprintf(stderr, "\n");
    fprintf(stderr, "Options list with default values:\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "    -h | --help              This message\n");
    fprintf(stderr, "    -V | --version           Print Version and exit\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "    -q | --quiet             Disable output (debug level 0)\n");
    fprintf(stderr, "    -v | --verbose           Verbose output (debug level 4)\n");
    fprintf(stderr, "    -d | --debug             Debug level (%d)\n", SIMPLEFTPD_DEFAULT_CONFIG_DEBUG_LEVEL);
    fprintf(stderr, "                             0 DISABLE (quiet)\n");
    fprintf(stderr, "                             1 ERROR\n");
    fprintf(stderr, "                             2 WARNING\n");
    fprintf(stderr, "                             3 INFO\n");
    fprintf(stderr, "                             4 DEBUG (verbose)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "    -p | --tcp-port          TCP listening port (%d)\n", SIMPLEFTPD_DEFAULT_CONFIG_TCP_PORT);
    fprintf(stderr, "\n");
}

void ui_message(int level, const char *where, char *input, ...) {
    va_list args;
    char datetime[20];
    time_t rawtime;
    struct tm *timeinfo;
    char content[131072];
    char prefix[1025];
    char where_str[65];

    rawtime = time(NULL);
    timeinfo = localtime(&rawtime);
    strftime(datetime, 20, "%Y-%m-%d %H:%M:%S", timeinfo);

    bzero(where_str, sizeof(where_str));
    if (strlen(where) > 0)
        snprintf(where_str, sizeof(where_str) - 1, "{%s} ", where);

    va_start(args, input);

    bzero(prefix, sizeof(prefix));
    if (level == UI_ERROR)
        sprintf(prefix, "%s [ERROR] %s", datetime, where_str);
    if (level == UI_WARNING)
        sprintf(prefix, "%s [WARN]  %s", datetime, where_str);
    if (level == UI_INFO)
        sprintf(prefix, "%s [INFO]  %s", datetime, where_str);
    if (level == UI_DEBUG)
        sprintf(prefix, "%s [DEBUG] %s", datetime, where_str);

    bzero(content, sizeof(content));
    vsprintf(content, input, args);

    va_end(args);

    if (level <= config->debug_level)
        fprintf(stderr, "%s%s\n", prefix, content);
}
