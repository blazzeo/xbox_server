#include "tcp_client_impl.h"
#include <boost/asio/io_context.hpp>
#include <cstdlib>
#include <format>
#include <iostream>
#include <ostream>

enum class operation {
    SEND = 1,
    STOP = 0,
};

int main(int argc, char *argv[]) {
    auto name = std::format("{}", (argc > 1) ? argv[1] : "client");
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);

    auto endpoint{resolver.resolve("127.0.0.1", "5001")};

    TCP_Client client(name, io_context, std::move(endpoint));

    client.start();

    while (true) {
        auto choice{0};
        std::cout << "1 - send,\t0 - stop\n";
        std::cout << "Operation: ";
        std::cin >> choice;

        switch ((operation)choice) {
        case operation::SEND: {
            std::string msg;
            std::cout << "Message: ";
            std::cin >> msg;
            client.send(msg + '\n');
            client.read(msg);
            std::cout << "Recv: " << msg << std::endl;
            break;
        }

        case operation::STOP:
            exit(0);
        }
    }

    return 0;
}
