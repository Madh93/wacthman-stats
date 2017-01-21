// NAME          : server.c
// DESCRIPTION   : Stats server
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3

#include "server.h"


// Signal handling

void signalHandler(int signo) {
    if (signo == SIGINT) {
        printf("LOG_INFO: Received SIGINT");
        waiting = 0;
    } else {
        printf("LOG_ERR: Received unknown signal");
        exit(EXIT_FAILURE);
    }
}


// General

int initServer(int port) {

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        printf("LOG_NOTICE: Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server;

    // Add server socket info
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Bind name to socket
    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("LOG_ERROR: Failed to bind to socket\n");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(sockfd, MAX_CONNECTIONS) < 0) {
        printf("LOG_ERROR: Failed to listen on socket\n");
        exit(EXIT_FAILURE);
    }

    // Start to waiting new connections
    waiting = 1;
    printf("LOG_INFO: Started server in port %d\n", port);

    return sockfd;
}


void closeServer(int sockfd) {

    if (close(sockfd) < 0) {
        printf("LOG_ERR: Failed to close server\n");
        exit(EXIT_FAILURE);
    }

    printf("LOG_INFO: Server closed\n");
}


int listenMessages(int fd) {

    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    ssize_t count = read(fd, buffer, sizeof(buffer));

    if (count < 0) {
        printf("LOG_ERR: Failed to read message from client\n");
    } else if (count == 0) {
        printf("LOG_INFO: Client has disconnected\n");
    } else {
        printf("LOG_INFO: Client says: %s\n", buffer);
    }

    return count;
}


void sendMessage(int fd, char *message) {

    if (write(fd, message, strlen(message)) < 0) {
        printf("LOG_ERR: Failed to send message to client");
        exit(EXIT_FAILURE);
    }
}


void waitForRequests(int sockfd) {

    struct sockaddr_in client;
    socklen_t clientlen = sizeof(client);

    // Accept connection
    int newsockfd = accept(sockfd, (struct sockaddr*)&client, &clientlen);

    if (newsockfd < 0) {
        printf("LOG_ERROR: Failed to accept connection\n");
        exit(EXIT_FAILURE);
    }

    printf("LOG_NOTICE: New connection from %s\n", inet_ntoa(client.sin_addr));
    sendMessage(newsockfd, (char*)"Welcome!");

    // Listen client messages
    while(listenMessages(newsockfd));

    close(newsockfd);
}


int runServer(int port) {

    // Register signal SIGTERM and signal handler
    signal(SIGTERM, signalHandler);

    // Get TCP socket
    int sockfd = initServer(port);

    // Client petitions loop
    while(waiting) {
        waitForRequests(sockfd);
    }

    // Close and free
    closeServer(sockfd);

    return 0;
}


void showHelp() {
    printf("%s: Stats server for Watchman\n", APP);
    printf("\nUsage: %s [options]\n", APP);
    printf("\nOptions:\n");
    printf("  -p, --port          Number port\n");
    printf("  -h, --help          Show this help\n");
    printf("  -v, --version       Show version\n");
}

void showVersion() {
    printf("%s %s\n", APP, VERSION);
}
