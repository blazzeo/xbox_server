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

void Server::broadcast_echo(std::string_view message) {
    for (auto &client : clients_pool)
        write(client.socket, buffer(message));
}

//	Disconnect by client struct
void Server::disconnect_user(Client_info &client) {
    auto it = std::find(clients_pool.begin(), clients_pool.end(), client);

    if (it != clients_pool.end())
        clients_pool.erase(it);
}

//	Disconnect by client id
void Server::disconnect_user(int id) {
    auto it = std::find(clients_pool.begin(), clients_pool.end(), id);

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
            auto len = read_until(cs, dynamic_buffer(client_name), '0');

            if (len == 0) {
                std::cerr << "Error: Client disconnected before sending name\n";
                return;
            }

            client_name.erase(
                std::find(client_name.begin(), client_name.end(), '0'),
                client_name.end());

            if (cs.is_open())
                write(cs, buffer("OK0"));

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
