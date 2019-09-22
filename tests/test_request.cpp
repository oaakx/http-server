#include <iostream>
#include <cassert>
#include "../constants.hpp"
#include "../request.hpp"
using namespace std;

void test_split_header_lines() {
    string A = "GET / HTTP/1.1";
    string B = "Host: localhost:8080";
    string C = "Connection: keep-alive";
    string request = A + CRLF + B + CRLF + C + CRLF;
    vector<string> lines = split_header_lines(request);

    assert(lines.size() == 4);
    assert(lines[0] == A);
    assert(lines[1] == B);
    assert(lines[2] == C);
    assert(lines[3] == "");
}

void test_parse_request_line() {
    // 1
    string request_line = "GET / HTTP/1.1";
    string method, uri, version;

    parse_request_line(request_line, method, uri, version);

    assert(method == "GET");
    assert(uri == "/");
    assert(version == "HTTP/1.1");

    // 2
    request_line = "  \t      POST   /search?q=yeet  HTTP/1.1  ";

    parse_request_line(request_line, method, uri, version);

    assert(method == "POST");
    assert(uri == "/search?q=yeet");
    assert(uri != "/search");
    assert(version == "HTTP/1.1");
}

void test_parse_header() {
    string name = "Host";
    string value = "localhost";
    string header = name + ": " + value;

    string name_, value_;
    parse_header(header, name_, value_);

    assert(name == name_);
    assert(value == value_);
}

int main() {
    test_split_header_lines();
    cout << "Passed: split_header_lines\n";

    test_parse_request_line();
    cout << "Passed: parse_request_line\n";

    test_parse_header();
    cout << "Passed: parse_header\n";

    return 0;
}
