#include <vector>
#include <string>
#include <cstring>
#include "unistd.h"
#include "constants.hpp"
#include "exceptions.hpp"
#include "request.hpp"

vector<string> split_lines();
void parse_request_line();
void parse_header();
void parse_request();

/*
    Splits request into separate lines (with CRLF as delimiter).

    Returns split lines.
    Treats lines that end with only LF as if they end with CRLF.
*/
vector<string> split_header_lines(const string &request) {
    size_t last = 0, next;
    vector<string> header_lines;
    string token;

    while ((next = request.find(LF, last)) != string::npos) {
        if (next > 0 && request[next-1] == CR)
            token = request.substr(last, next-1 - last);
        else
            token = request.substr(last, next-last);

        last = next+1;
        header_lines.push_back(token);
    }
    token = request.substr(last, string::npos);
    header_lines.push_back(token);

    return header_lines;
}


/*
    Reads until CRLF CRLF (that is, until end of headers section
    of HTTP message).

    Also, treats LF LF the same way.
    Returns what is read, excluding last CRLF (or last lF
    in the case of double LF).
*/
string read_until_double_crlf(int connfd) {
    char c;
    int nread;
    string data;

    while ((nread = read(connfd, &c, 1)) > 0) {
        data.push_back(c);

        if (c == LF) {  
            if (data.length() >= 4
                    && strcmp(data.c_str() + data.length() - 4,
                        CRLF CRLF) == 0) {
                data.pop_back();
                data.pop_back();
                break;
            }
            else if (data.length() >= 2
                    && strcmp(data.c_str() + data.length() - 2, LFLF) == 0) {
                data.pop_back();
                break;
            }
        }
    }

    return data;
}


/*
    Parses request line REQLINE (= the very first line of request message).
*/
void parse_request_line(const string &reqline,
                   string &method,
                   string &uri,
                   string &version) {
    // method
    size_t start = first_nonws(reqline);
    size_t end = first_ws(reqline, start);
    method = reqline.substr(start, end - start);

    // uri
    start = first_nonws(reqline, end);
    end = first_ws(reqline, start);
    uri = reqline.substr(start, end - start);

    // version
    start = first_nonws(reqline, end);
    end = first_ws(reqline, start);
    version = reqline.substr(start, end - start);

    //if (method == "" || uri == "" || version == "")
    //    throw InvalidMessageSyntax();
}


/*
    Parses header field HEADER into:
    * NAME      - header field name
    * VALUE     - header field value
*/
void parse_header(const string &header,
                  string &name,
                  string &value) {
    // ABNF grammar:
    //   header = name ":" OWS value OWS
    //   OWS    = *(" " / HTAB)          ; optional whitespace

    // name
    size_t pos = header.find(':');

    if (pos == string::npos)
        throw InvalidMessageSyntax();

    name = header.substr(0, pos);

    // value
    size_t start = first_nonws(header, pos+1);
    size_t end = first_ws(header, start);
    value = header.substr(start, end - start);
}


/*
    Reads request header from connection socket CONNFD
    and parses following from it:
    * METHOD    - request method
    * URI       - URI to requested target
    * VERSION   - HTTP version
    * HEADERS   - request headers
    * BODY      - request body (if present, or empty string otherwise)
*/
void parse_request(int connfd,
                   string &method,
                   string &uri,
                   string &version,
                   map<string, string> &headers,
                   string &body) {
    string request = read_until_double_crlf(connfd);
    vector<string> header_lines = split_header_lines(request);

    parse_request_line(header_lines[0], method, uri, version);

    string name, value;
    for (int i = 1; i < (int)header_lines.size(); i++) {
        if (header_lines[i] == "")
            continue;

        parse_header(header_lines[i], name, value);
        headers[name] = value;
    }
}

