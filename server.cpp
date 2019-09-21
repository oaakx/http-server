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
#include <thread>

using namespace std;

void handle_connection(int);

const int MAX_PENDING_CONNECTIONS = 10000; // backlog for listen()
const int BUFFER_SIZE = 256;
const string SAMPLE_HTTP_RESPONSE =
    "HTTP/1.1 200 OK\r\n"
    "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
    "Server: Apache/2.2.14 (Win32)\r\n"
    "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n"
    "Content-Type: text/html\r\n"
    "Connection: Closed\r\n"
    "\r\n"
    "<html>\r\n"
    "<body>\r\n"
    "<h1>Hello, World!</h1>\r\n"
    "</body>\r\n"
    "</html>\r\n";


void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

/* void client() {
    socket();
    connect();

    // session
    send();
    receive();
} */

void server(char *port) {
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");


    int portno;
    portno = atoi(port);

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; // internet domain
    serv_addr.sin_addr.s_addr = INADDR_ANY; // bind to all
    serv_addr.sin_port = htons(portno);

    if  (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
        error("ERROR binding to port");

    listen(sockfd, MAX_PENDING_CONNECTIONS);

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    // Accept incoming connections, one at a time.
    std::vector<std::thread *> threads;
    int newsockfd;
    while (newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr,
                  &clilen)) {
        if (newsockfd < 0) {
           error("ERROR accepting");
           continue;
        }

        std::thread *thp = new std::thread(handle_connection, newsockfd);
        threads.push_back(thp);
    }

    for (auto thp: threads) {
        thp->join();
        delete thp;
        cout << "Thread finished\n";
    }

    close(sockfd);
}

void handle_connection(int newsockfd) {
    char buffer[BUFFER_SIZE];
    int nread = read(newsockfd, buffer, BUFFER_SIZE);
    if (nread < 0)
        error("ERROR reading from socket");

    cout << "\nRead this message:\n" << buffer << "\nEND\n";

    int nwritten = write(newsockfd, SAMPLE_HTTP_RESPONSE.c_str(), SAMPLE_HTTP_RESPONSE.length());
    if (nwritten < 0)
        error("ERROR writing to socket");

    close(newsockfd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "ERROR incorrect argument format\n";
        cerr << "Usage: ./main PORT\n";
        exit(EXIT_FAILURE);
    }

    server(argv[1]);

    return 0;
}
