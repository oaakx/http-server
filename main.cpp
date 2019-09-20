#include <iostream>
using namespace std;

void client() {
    socket();
    connect();

    // session
    send();
    receive();
}

void server() {
    socket();
    bind();
    listen();
    while (true) {
        accept();

        // session
        send();
        receive();
    }
}

int main() {
    

    return 0;
}
