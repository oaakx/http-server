#pragma once
#include <string>
#include <fstream>
using namespace std;

class InvalidURI : public std::exception { };

string get_absolute_path(const string &uri);
void get_file_by_uri(const string &uri, const string &serve_dir,
        ifstream &target_file);

