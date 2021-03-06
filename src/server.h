// NAME          : server.h
// DESCRIPTION   : Stats server
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3


#ifndef SERVER_H
#define SERVER_H

// To run server
#include "connection.h"
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
#include <pthread.h>


// Utilities
#define MAX_CONNECTIONS 5

// Monitor status
static int waiting = 0;

// Signal handling
void signalHandler(int signo);

// General
int initServer(int port);
void closeServer(int sockfd);

void sendMessage(int fd, char *message);
void waitForRequests(int sockfd);

// Server big loop
int runServer(int port);

#endif /* SERVER_H */
