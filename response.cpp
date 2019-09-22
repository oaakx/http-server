#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "unistd.h"
#include "exceptions.hpp"
#include "constants.hpp"
#include "uri.hpp"
#include "response.hpp"
using namespace std;


/*
    Write response header to CONNFD.
*/
void generate_response_header(const string &version,
                       int status,
                       const string &reason,
                       map<string, string> headers,
                       int connfd) {
    // Status line
    string status_line = version + " " + to_string(status) + " " + reason + CRLF;
    write(connfd, status_line.c_str(), status_line.length());

    // Headers
    // TODO it's good to write certain headers first
    for (auto const& kv: headers) {
        string header = kv.first + ": " + kv.second + CRLF;
        write(connfd, header.c_str(), header.length());
    }

    // Empty line
    write(connfd, CRLF, 2);
}


/*
    Return size of file open as ifstream FILE.
    
    Note, seekg() is called on FILE.
*/
size_t get_file_size(ifstream &file) {
    // get size
    std::streampos begin = file.tellg();
    file.seekg(0, ios::end);
    std::streampos end = file.tellg();

    // reset seek
    file.clear();
    file.seekg(0, ios::beg);

    return end - begin;
}


/*
    Respond with 501 Not Implemented.
*/
void respond_501(int connfd) {
    int status = STATUS_NOT_IMPLEMENTED;
    string reason = "Not Implemented";
    map<string, string> headers;
    headers["Content-Length"] = "0";
    headers["Connection"] = "close";

    generate_response_header(HTTP_VERSION, status, reason,
        headers, connfd);
}


/*
    Respond with 404 Not Found.
*/
void respond_404(int connfd) {
    int status = STATUS_NOT_FOUND;
    string reason = "Not Found";
    map<string, string> headers;
    headers["Content-Length"] = "0";
    headers["Connection"] = "close";

    generate_response_header(HTTP_VERSION, status, reason,
        headers, connfd);
}

/*
    Serve a file corresponding to URI.
*/
void serve_file(const string &serve_dir, const string &uri, int connfd) {
    ifstream target_file;
    string mime_type;

    try {
        get_fileinfo_by_uri(uri, serve_dir, target_file, mime_type);
    }
    catch (InvalidURI) {
        respond_404(connfd);
        return;
    }

    int status = STATUS_OK;
    string reason = "OK";
    map<string, string> headers;
    headers["Content-Length"] = to_string(get_file_size(target_file));
    if (mime_type != "")
        headers["Content-Type"] = mime_type;
    headers["Connection"] = "close";

    generate_response_header(HTTP_VERSION, status, reason,
        headers, connfd);

    // Write file data to message body
    char c;
    while (target_file.get(c))
        write(connfd, &c, 1);
}

