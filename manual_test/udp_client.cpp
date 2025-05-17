#include "udp_client_impl.h"
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <cstdlib>
#include <format>
#include <iostream>
#include <ostream>

enum class operation { SEND = 1, STOP = 0 };

int main(int argc, char *argv[]) {
    std::string name = std::format("{}", (argc > 1) ? argv[1] : "client");
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);

    boost::asio::ip::address addr = boost::asio::ip::make_address("127.0.0.1");
    boost::asio::ip::udp::endpoint endpoint(addr, 5001);

    UDP_Client client(name, io_context, endpoint);

    while (true) {
        auto choice{0};
        std::cout << "1 - send,\t0 - stop\n";
        std::cout << "Operation: ";
        std::cin >> choice;

        switch ((operation)choice) {
        case operation::SEND: {
            std::string send_msg;
            std::cout << "Message: ";
            std::cin >> send_msg;
            client.send(send_msg);
            auto recv_msg = client.recv();
            std::cout << "Recv: " << recv_msg << std::endl;
            break;
        }

        case operation::STOP:
            exit(0);
        }
    }

    return 0;
}
