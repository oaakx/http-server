#pragma once
#include <string>
using namespace std;

#define CR      '\r'
#define LF      '\n'
#define CRCR    "\r\r"
#define LFLF    "\n\n"
#define CRLF    "\r\n"

const string HTTP_VERSION = "HTTP/1.1";

#define STATUS_OK               200
#define STATUS_NOT_FOUND        404
#define STATUS_NOT_IMPLEMENTED  501
#define STATUS_BAD_REQUEST      400

