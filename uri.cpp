#include <string>
#include <iostream>
#include <sys/stat.h>
#include "exceptions.hpp"
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
    Check if string S ends with string E.
*/
inline bool ends_with(const string &s, const string &e) {
    return s.length() >= e.length()
        && s.compare(s.length() - e.length(), e.length(), e) == 0;
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
void get_fileinfo_by_uri(const string &uri, const string &serve_dir,
        ifstream &target_file, string &mime_type) {
    string rel_path = get_absolute_path(uri);
    string local_path = serve_dir + rel_path;

    // Check if file exits (and is not directory)
    struct stat s;
    if (stat(local_path.c_str(), &s) < 0 || s.st_mode & S_IFDIR)
        throw InvalidURI();

    // Open ifstream
    target_file.open(local_path);
    cerr << "path: " << local_path << "\n";

    // Mime type
    // TODO far-from-complete list
    mime_type = "";

    if (ends_with(rel_path, ".html") || ends_with(rel_path, ".htm"))
        mime_type = "text/html";
    else if (ends_with(rel_path, ".css"))
        mime_type = "text/css";
    else if (ends_with(rel_path, ".jpg") || ends_with(rel_path, ".jpeg"))
        mime_type = "image/jpeg";
    else if (ends_with(rel_path, ".png"))
        mime_type = "image/png";
}
