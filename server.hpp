#pragma once
#include ?

const int MAX_PENDING_CONNECTIONS = 20000; // backlog for listen()
const int BUFFER_SIZE = 256;

void start_server(int port, const string &serve_dir);

// temp
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
