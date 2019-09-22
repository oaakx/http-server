#include <iostream>
#include "args.hpp"
#include "server.hpp"
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

    cout << "Serving dir=" << serve_dir << " on port=" << port << " ...\n";
    start_server(port, serve_dir);

    return 0;
}
