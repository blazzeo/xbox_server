#include "server_impl.h"
#include <iostream>

using boost::asio::read, boost::asio::buffer, boost::asio::write;

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

void Server::start() { is_available.store(true); }
void Server::stop() { is_available.store(false); }

void Server::accept_users() {
    while (true) {
        tcp::socket client_socket(io_context);
        acceptor_.accept(client_socket);

        if (not is_available.load()) {
            write(client_socket, buffer("not_available"));
            std::cout << "Connection failed: server not available\n";
            continue;
        }

        char name_buffer[128];
        size_t len = read(client_socket, buffer(name_buffer));
        std::string client_name(name_buffer, len);

        clients_pool.push_back(Client_info(clients_count++, client_name,
                                           std::move(client_socket)));

        std::cout << "Client " << client_name << " connected.\n";
    }
}
