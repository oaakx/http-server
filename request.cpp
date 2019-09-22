#include <vector>
#include <string>
#include "constants.h"

vector<string> split_lines();
void parse_request_line();
void parse_header();
void parse_request();


/*
    Parses raw request into request body and lines preceding the body.

    Assigns message body to BODY.
    Returns lines preceding the body as vector<string>'s excluding
    CRLF at the end.
    Forgives line endings with just LF (that is, without CR).
*/
vector<string> split_lines(const string &request, string &body) {
    size_t last_idx = 0;

    while (last_idx < (int) request.length())  {
        size_t cur_idx = request.find(LF, last_idx + 1);

        if (cur_idx > 0 && request
    }
}


/*
    Parses raw REQUEST into:
    * METHOD    - request method
    * URI       - URI to requested target
    * VERSION   - HTTP version
    * HEADERS   - request headers
    * BODY      - request body (if present, or empty string otherwise)
*/
void parse_request(const string &request,
                   string &method,
                   string &uri,
                   string &version,
                   map<string, string> &headers,
                   string &body) {
    vector<string> lines = split_lines(request, &body);

    parse_request_line(lines[0], method, uri, version);

    string name;
    string value;
    for (int i = 1; i < (int)lines.len(); i++) {
        parse_header(lines[i], name, value);
        headers[name] = value;
    }
}
