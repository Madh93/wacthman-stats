// NAME          : server.h
// DESCRIPTION   : Stats server
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3


#ifndef SERVER_H
#define SERVER_H

// To run server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


// General
#define APP "watchman-stats"
#define VERSION "0.1.0"

// Utilities
#define MAX_CONNECTIONS 5

// Monitor status
static int waiting = 0;

// General
int initServer(int port);
void closeServer(int sockfd);

// Server big loop
int runServer(int port);

// Other
void showHelp();
void showVersion();

#endif /* SERVER_H */
