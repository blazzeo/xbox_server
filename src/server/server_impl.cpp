#include "server_impl.h"
#include "dbg.h"
#include <boost/asio/buffer.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/registered_buffer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include <unistd.h>

using boost::asio::read_until, boost::asio::dynamic_buffer, boost::asio::buffer,
    boost::asio::write;

void Server::broadcast_echo(std::string message) {
    for (auto &client : clients_pool)
        write(client.socket, buffer(message));
}

//	Disconnect by client id
void Server::disconnect_user(int id) {
    auto it = std::find(clients_pool.begin(), clients_pool.end(), id);

    dbg(*it);

    if (it != clients_pool.end())
        clients_pool.erase(it);
}

void Server::start() { is_available = true; }
void Server::stop() { is_available = false; }

void Server::accept_users() {
    while (is_available) {
        try {
            tcp::socket cs(io_context);
            m_acceptor.accept(cs);

            std::cout << "connection attempt...\n";

            //	Client's name
            std::string client_name{};
            auto len = read_until(cs, dynamic_buffer(client_name), '\n');

            if (len == 0)
                throw "Error: Client disconnected before sending name\n";

            client_name.erase(
                std::find(client_name.begin(), client_name.end(), '\n'),
                client_name.end());

            if (cs.is_open())
                write(cs, buffer("OK\n"));

            clients_pool.emplace_back(++clients_count, client_name,
                                      std::move(cs));

            std::cout << "Client ID: " << clients_count
                      << ", name: " << client_name << " connected.\n";

        } catch (const boost::system::system_error &e) {
            if (e.code() == boost::asio::error::eof) {
                std::cout << "Client disconnected.\n";
            } else {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}

void Server::accept_udp() {
    while (is_available) {
        try {
            char recv_msg[128];
            boost::asio::ip::udp::endpoint sender_endpoint;
            udp_socket.receive_from(boost::asio::buffer(recv_msg),
                                    sender_endpoint);

            udp_socket.send_to(
                boost::asio::buffer(std::format("ECHO_{}", recv_msg)),
                sender_endpoint);
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
