test_parse_args() {
    int port;
    string serve_dir;

    parse_args(5, ["http-server", "--dir", "/var/www/html", "--port", "8080"],
        port, serve_dir);
}

bool test_args() {

}