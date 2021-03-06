/*
** Copyright (C) 2011 Tim Shelton
** Copyright (C) 2011 HAWK Network Defense, Inc. hawkdefense.com
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License Version 2 as
** published by the Free Software Foundation.  You may not use, modify or
** distribute this program under any other version of the GNU General
** Public License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef __OP_SYSLOG_FULL_H_
#define __OP_SYSLOG_FULL_H_


#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "barnyard2.h"
#include "map.h"
#include "mstring.h"
#include "parser.h"
#include "plugbase.h"
#include "strlcpyu.h"
#include "unified2.h"


#define OUT_MODE_DEFAULT 0
#define OUT_MODE_FULL 1

#define LOG_UDP 0
#define LOG_TCP 1


typedef struct _OpSyslog_Data 
{
    char *server;
    char *sensor_name;
    
    u_int8_t operation_mode;
    u_int8_t local_logging;
    u_int32_t syslog_priority;
    
    char syslog_tx_facility[16];
    char syslog_tx_priority[16];
    

    u_int32_t port;
    u_int16_t detail;
    u_int16_t proto;

    char delim;
    char field_separators;

    struct hostent *hostPtr;    
    struct sockaddr_in sockaddr;
    int socket;

    char *payload;
    char *formatBuffer;
    u_int32_t payload_current_pos;
    u_int32_t format_current_pos;

    
} OpSyslog_Data;

void OpSyslog_Setup(void);
void OpSyslog_Init(char *args);

#define SYSLOG_MAX_QUERY_SIZE 65535   /* This could be easely filled in log mode with  the full packet payload, 
				         we issue a warning if payload is truncated in log mode 
					 We could make the query size max payload *2 + 1024 or so bytes and we should be fine, but that would make large
					 syslog messages if reached and i wonder if SIEM would be able to handle that.
				      */

#endif  /* __OP_SYSLOG_FULL_H_ */

