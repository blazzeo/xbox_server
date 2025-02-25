#include "tcp_client_impl.h"
#include <boost/asio/io_context.hpp>
#include <cstdlib>
#include <format>
#include <iostream>

enum class operation { START = 0, STOP = 1, RUN = 2 };

int main(int argc, char *argv[]) {
    auto name = std::format("{}", (argc > 1) ? argv[1] : "client");
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);

    auto endpoint{resolver.resolve("127.0.0.1", "5001")};

    TCP_Client client(name, io_context, std::move(endpoint));

    while (true) {
        auto choice{0};
        std::cout << "Operation: ";
        std::cin >> choice;

        switch ((operation)choice) {
        case operation::START:
            std::cout << "start\n";
            client.start();
            break;
        case operation::RUN:
            std::cout << "run\n";
            client.run();
            break;
        case operation::STOP:
            std::cout << "stop\n";
            exit(0);
        }
    }

    return 0;
}
