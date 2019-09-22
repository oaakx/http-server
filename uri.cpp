#include <string>
#include <iostream>
#include "uri.hpp"
using namespace std;

/*
    Returns absolute-path of URI.

    For now, URI must be in origin-form.
    It just returns URI without the query part.
    (See RFC 7230 Section 5.3)
*/
string get_absolute_path(const string &uri) {
    size_t query_idx = uri.find('?');
    if (query_idx == string::npos)
        return uri;

    return uri.substr(0, query_idx);
}

/*
    Identifies file to be served (formally, requested target resource)
    by URI and SERVE_DIR.

    Returns ifstream to the target resource.
    URI can be only in origin-form (see RFC 7230 Section 5.3).
    Other forms are not supported yet, because OPTIONS and CONNECT
    methods aren't.

    Throws UnvalidURI if no matching file is found.
*/
void get_file_by_uri(const string &uri, const string &serve_dir,
        ifstream &target_file) {
    string rel_path = get_absolute_path(uri);
    string local_path = serve_dir + rel_path;

    target_file.open(local_path);

    cerr << "path: " << local_path << "\n";

    if (target_file.fail())
        throw InvalidURI();
}
