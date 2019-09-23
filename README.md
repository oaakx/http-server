# http-server

> Simple HTTP/1.1 server in C++

When implementing this HTTP/1.1 server, I referred to the following more refined RFCs (instead of the original RFC2616):

 * RFC7230 - HTTP/1.1: Message Syntax and Routing
 * RFC7231 - HTTP/1.1: Semantics and Content
 * RFC7232 - HTTP/1.1: Conditional Requests
 * RFC7233 - HTTP/1.1: Range Requests
 * RFC7234 - HTTP/1.1: Caching
 * RFC7235 - HTTP/1.1: Authentication

For more info, see [RFC2616 is Dead](https://www.mnot.net/blog/2014/06/07/rfc2616_is_dead).

# TODO

- [ ] Measure performance
    - Number of requests per second
    - Number of concurrent connections

# Features

Currently available:

- [x] IPv4 only
- [x] Serving static files
- [x] Methods: only `GET`
- [x] MIME types: `text/html`, `text/css`, `image/jpg`, `image/png`

NOT available yet:

- [ ] IPv6
- [ ] Multipart data
- [ ] Conditional requests
- [ ] Range requests
- [ ] Basic authentication over HTTP
- [ ] Methods: `HEAD`, `POST`, `PUT`, `DELETE`, `CONNECT`, `OPTIONS`, `TRACE`

# How to build and run

Build using:

    make build

It will generate an output executable `http-server`. To run it:

    ./http-server --dir tests/sample-serve-dir --port 8080

Go to [`localhost:8080/index.html`](http://localhost:8080/index.html) on your browser. If you go to `localhost:8080` you will get 404 Not Found error.

# Future work

- [ ] Restructure code from C-style method collection to C++ OOP approach (`future` subdirectory)
- [ ] Migrate tests to [Google Test](https://github.com/google/googletest)
- [ ] Audit security
  - Review "Security Considerations" sections (in all of above mentioned RFCs)
  - **Known issue:** Currently, requesting `/../somefile` will serve a file outside of the served directory, which is a security disaster.

# Acknowledgments

- A refresher on Unix Socket Programming: http://www.linuxhowtos.org/C_C++/socket.htm
