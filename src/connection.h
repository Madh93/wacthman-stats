// NAME          : connection.h
// DESCRIPTION   : Client connection handling
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3

#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// General
int initConnection(int sockfd);
void closeConnection(int sockfd);

int listenMessages(int fd);

// Handle connection
void* runConnection(void *fd);

#endif /* CONNECTION_H */
