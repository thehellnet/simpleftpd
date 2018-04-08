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

#ifndef __LIBSIMPLEFTP_COMMAND_H
#define __LIBSIMPLEFTP_COMMAND_H

#define SIMPLEFTPD_FTP_SUCCESS_SYNTAX_GENERIC 200
#define SIMPLEFTPD_FTP_SUCCESS_CONNECTION_READY 220

/*
 * 2yz – Success reply
4yz or 5yz – Failure reply
1yz or 3yz – Error or Incomplete reply
The second digit defines the kind of error:

x0z – Syntax. These replies refer to syntax errors.
x1z – Information. Replies to requests for information.
x2z – Connections. Replies referring to the control and data connections.
x3z – Authentication and accounting. Replies for the login process and accounting procedures.
x4z – Not defined.
x5z – File system. These replies relay status codes from the server file system.

 */

#include "context.h"

void simpleftp_response_success_connection_ready(char *buffer, simpleftp_context *context);

#endif
