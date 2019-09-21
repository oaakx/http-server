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

# Features

Currently available:

- ...

Not available yet:

- [ ] IPv4 only
- [ ] Serving static files
- [ ] IPv6
- [ ] Multipart data
- [ ] Conditional requests
- [ ] Range requests
- [ ] Basic authentication over HTTP

# Future work

- [ ] Improve security
  - Review "Security Considerations" sections (in above mentioned RFCs)

# Acknowledgments

- A refresher on Unix Socket Programming: http://www.linuxhowtos.org/C_C++/socket.htm