#include <iostream>
#include <fstream>
#include <string>
#include "../uri.hpp"
using namespace std;

int main() {
    string uri = "/stanford.png";
    string serve_dir = "tests/sample-serve-dir";
    ifstream fin;
    
    try {
        get_file_by_uri(uri, serve_dir, fin);
    }
    catch (InvalidURI) {
        cout << "ERROR invalid uri (file not found)\n";
        exit(EXIT_FAILURE);
    }

    cout << "File exists!\n";
    return 0;
}
