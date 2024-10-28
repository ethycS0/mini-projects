#include"include/server.h"

int main() {
    using namespace http;

    Server server = Server("0.0.0.0", 6969);
    server.startListen();
}
