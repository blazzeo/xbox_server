#include "tcp_client_impl.h"
#include <boost/asio/io_context.hpp>
#include <format>

int main(int argc, char *argv[]) {
    auto name = std::format("{}", (argc > 1) ? argv[1] : "client");
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);

    auto endpoint{resolver.resolve("127.0.0.1", "5001")};

    TCP_Client client(name, io_context, endpoint);
    client.run();

    return 0;
}
