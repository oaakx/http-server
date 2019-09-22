#pragma once
#include <string>
#include <fstream>
using namespace std;

string get_absolute_path(const string &uri);
void get_fileinfo_by_uri(const string &uri, const string &serve_dir,
        ifstream &target_file, string &mime_type);

