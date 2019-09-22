#pragma once
#include <string>
using namespace std;

const string USAGE =
    "ERROR invalid arguments\n"
    "\n"
    "Usage: http-server [--port PORT] [--dir SERVE_DIR]\n"
    "\n"
    "    --port -p  port to serve in\n"
    "    --dir  -d  directory to serve files from\n";

const unsigned short DEFAULT_PORT = 80;
const string DEFAULT_DIR = ".";

class ArgError : public exception { };

void parse_args(int argc, char* argv[], int &port,
        string &serve_dir);
