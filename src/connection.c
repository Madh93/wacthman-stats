// NAME          : connection.c
// DESCRIPTION   : Client connection handling
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3

#include "connection.h"

// General

int initConnection(int sockfd) {

    struct sockaddr_in client;
    socklen_t clientlen = sizeof(client);

    // Accept connection
    int newsockfd = accept(sockfd, (struct sockaddr*)&client, &clientlen);

    if (newsockfd < 0) {
        syslog(LOG_ERR, "Failed to accept connection");
        exit(EXIT_FAILURE);
    }

    syslog(LOG_NOTICE, "New connection from %s", inet_ntoa(client.sin_addr));

    return newsockfd;
}


void closeConnection(int sockfd) {
    close(sockfd);
}


int listenMessages(int fd) {

    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    ssize_t count = read(fd, buffer, sizeof(buffer));

    if (count < 0) {
        syslog(LOG_ERR, "Failed to read message from client");
    } else if (count == 0) {
        syslog(LOG_INFO, "Client has disconnected");
    } else {
        syslog(LOG_INFO, "Client says: %s", buffer);
    }

    return count;
}


// Handle connection

void* runConnection(void *fd) {

    int sockfd = *(int*)fd;

    // Listen client messages
    while(listenMessages(sockfd));

    closeConnection(sockfd);
}
