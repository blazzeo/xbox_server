#include "server_impl.h"
#include <boost/asio/io_context.hpp>

int main(int argc, char *argv[]) {
    boost::asio::io_context io_context;

    Server server{io_context, 5001};

    server.start();
    server.accept_users();

    return 0;
}
