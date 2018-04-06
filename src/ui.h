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

#ifndef __ALEVEL_UI_H
#define __ALEVEL_UI_H

#define UI_DISABLE 0
#define UI_ERROR 1
#define UI_WARNING 2
#define UI_INFO 3
#define UI_DEBUG 4

void ui_usage();

void ui_version();

void ui_help();

void ui_message(int level, const char *where, char *input, ...);

#endif
