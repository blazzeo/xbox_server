#include "server_impl.h"
#include <boost/asio/io_context.hpp>
#include <cstdlib>
#include <iostream>

enum class operation { SEND = 1, BROAD = 2, BAN = 3, CLOSE = 0 };

int main(int argc, char *argv[]) {
    boost::asio::io_context io_context;
    Server server{io_context, 5001};
    server.start();

    while (true) {
        auto choice{0};
        std::cout << "1 - send\t2 - broadcast\t3 - ban\t0 - close\n";
        std::cout << "Operation: ";
        std::cin >> choice;

        switch ((operation)choice) {
        case operation::SEND:
            std::cout << "send placeholder\n";
            break;
        case operation::BROAD:
            server.broadcast_echo("broadcast_msg\n");
            break;
        case operation::BAN: {
            int id{0};
            std::cout << "\nUser id: ";
            std::cin >> id;
            server.disconnect_user(id);
            break;
        }
        case operation::CLOSE:
            exit(0);
        }
    }

    return 0;
}
