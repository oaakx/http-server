#pragma once
#include <string>
#include <map>
#include <fstream>
using namespace std;


void generate_response_header(const string &version,
                       int status,
                       const string &reason,
                       map<string, string> headers,
                       int connfd);
size_t get_file_size(ifstream &file);
void respond_501(int connfd);
void respond_404(int connfd);
void serve_file(const string &serve_dir, const string &uri, int connfd);
