#pragma once
#include <string>
#include <map>
#include <vector>
using namespace std;

vector<string> split_header_lines(const string &request);
string read_until_double_crlf(int connfd);
void parse_request_line(const string &reqline,
                   string &method,
                   string &uri,
                   string &version);
void parse_header(const string &header,
                  string &name,
                  string &value);
void parse_request(int connfd,
                   string &method,
                   string &uri,
                   string &version,
                   map<string, string> &headers,
                   string &body);

/*
    Returns first position that is whitespace (space or tab)
    starting from S[POS], or S.length().
*/
inline size_t first_ws(const string &s, size_t pos = 0) {
    while (pos < s.length() &&
            s[pos] != ' ' && s[pos] != '\t')
        pos++;

    return pos;
}

/*
    Returns first position that is non-whitespace (not space or tab)
    starting from S[POS], or S.length().
*/
inline size_t first_nonws(const string &s, size_t pos = 0) {
    while (pos < s.length() &&
            (s[pos] == ' ' || s[pos] == '\t'))
        pos++;

    return pos;
}
