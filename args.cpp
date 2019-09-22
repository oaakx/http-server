#include <cstring>
#include "args.hpp"

/*
    Parses argv for options below.

    Options:
    --port -p   Port number. Assigned to PORT.
    --dir  -d   Directory to serve files from. Assigned to SERVE_DIR.
*/
void parse_args(int argc, char* argv[], int &port,
        string &serve_dir) {
    port = DEFAULT_PORT;
    serve_dir = DEFAULT_DIR;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--port") == 0 || strcmp(argv[i], "-p") == 0) {
            if (i+1 >= argc)
                throw ArgError();

            string value(argv[i+1]);
            try {
                port = stoi(value);
            } catch (...) {
                throw ArgError();
            }

            i++;
        }
        else if (strcmp(argv[i], "--dir") == 0 || strcmp(argv[i], "-d") == 0) {
            if (i+1 >= argc)
                throw ArgError();

            serve_dir = string(argv[i+1]);

            i++;
        }
        else
            throw ArgError();
    }
}

