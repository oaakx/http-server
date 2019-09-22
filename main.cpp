#include <iostream>
#include "args.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    int port;
    string serve_dir;

    try {
        parse_args(argc, argv, port, serve_dir);
    }
    catch (ArgError) {
        cout << USAGE;
        exit(EXIT_FAILURE);
    }

    // start_server(port, serve_dir);
    cout << "Port: " << port << "\n";
    cout << "Dir: " << serve_dir << "\n";

    return 0;
}
