#include <string>

#include "http.h"

namespace http {
    class Body;
    class Header;

    class Request;
    class Response;

    class Version {
        int major;
        int minor;

        Version(int major, int minor)
            : major(major), minor(minor) {}

        Version(string version) {
            auto i = version.find('.');
            string major_str = version.substr(0, i);
            string minor_str = version.substr(i+1, string::npos);
            parse_version(version, &major, &minor);
        }

        bool operator < (const Version &r) {
            return major < r.major
                || (major == r.major && minor < r.minor);
        }
    }

    enum Method { GET, HEAD, POST, PUT, DELETE, CONNECT,
                  OPTIONS, TRACE };

    class Body {}

    class Header {
        string name;
        string value;
    }

    class Request {
        public Method method;
        public string uri;
        public Version version;
        public vector<Header> headers;
        public Body body;
    };

    class Response {
        public Version version;
        public int status;
        public string status_desc;
        public vector<Header> headers;
        public Body body;
    }
}
