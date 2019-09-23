#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <map>
#include <thread>
#include "request.hpp"
#include "response.hpp"
#include "constants.hpp"
#include "server.hpp"
using namespace std;

void error(const char *msg);
int init_server(int port);
void handle_connection(int connfd, const string &serve_dir);


/*
    Prints error (using perror) and exits with failure.
*/
void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}


/*
    Do socket initialization for listening to port PORT.

    Returns server socket fd.
*/
int init_server(int port) {
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    // Turns SO_REUSEADDR option on.
    //
    // This allows reuse of the address in TIME_WAIT state.
    // That means if another process is using the address and it
    // is not in TIME_WAIT state, you get "already in use" error
    // regardless of the value of SO_REUSEADDR option.
    // (Which is what we want anyways!)
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        error("ERROR setsockopt(SO_REUSEADDR) failed");

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; // internet domain
    serv_addr.sin_addr.s_addr = INADDR_ANY; // bind to all addresses
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
        error("ERROR binding to port");

    if (listen(sockfd, MAX_PENDING_CONNECTIONS) < 0)
        error("ERROR listening to port");

    return sockfd;
}


/*
    Handles single session associated with NEWSOCKFD.
*/
void handle_connection(int connfd, const string &serve_dir) {
    string method;
    string uri;
    string version;
    map<string, string> headers;

    parse_request_header(connfd, method, uri, version, headers);

    // cerr << "method: " << method << "\n";
    // cerr << "uri: " << uri << "\n";
    // cerr << "version: " << version << "\n";

    if (method == "GET" && version == HTTP_VERSION)
        serve_file(serve_dir, uri, connfd);
    else {
        respond_501(connfd);
    }

    // cerr << "\n";
    close(connfd);
}


/*
    Start serving files from SERVE_DIR on port PORT.
*/
void start_server(int port, const string &serve_dir) {
    int sockfd = init_server(port);

    int newsockfd;
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    // Accept incoming connections
    while (newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr,
                  &clilen)) {
        if (newsockfd < 0)
           error("ERROR accepting connection");

        std::thread t(handle_connection, newsockfd, serve_dir);
        t.detach();
    }

    // Never reached
    close(sockfd);
}

// temp
// int main(int argc, char* argv[]) {
//     int port = 8080;
//     string serve_dir = "tests/sample-serve-dir";
//     start_server(port, serve_dir);
// 
//     return 0;
// }

