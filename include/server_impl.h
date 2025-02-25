#pragma once
#include "boost/asio.hpp"
#include "connection.h"
#include <atomic>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <utility>

using boost::asio::ip::tcp;

struct Client_info {
    int id;
    std::string name;
    std::unique_ptr<std::thread> client_connection;
    tcp::socket socket;

    Client_info(int id, std::string name, tcp::socket &&client_socket)
        : id(id), name(std::move(name)), socket(std::move(client_socket)),
          client_connection() {}

    ~Client_info() {
        if (client_connection->joinable())
            client_connection->join();
    }

    Client_info(const Client_info &other) = delete;
    Client_info &operator=(const Client_info &other) = delete;

    bool operator==(const Client_info &other) {
        return this->id == other.id and this->name == other.name;
    }

    bool operator==(int other_id) { return this->id == other_id; }
};

class Server {
    size_t clients_count;
    std::list<Client_info> clients_pool;
    std::atomic<bool> is_available;
    tcp::acceptor m_acceptor;
    boost::asio::io_context &io_context;

  public:
    //	io_context, port
    Server(boost::asio::io_context &io_context, short port)
        : io_context(io_context),
          m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
          is_available(false) {
        clients_count = 0;
    }

    ~Server() {
        for (auto &client : clients_pool) {
            if (client.client_connection->joinable())
                client.client_connection->join();
        }
    }

    //  Start server
    void start();
    //	Stop server
    void stop();
    //	Message to all the clients
    void broadcast_echo(std::string_view);
    //	Block user
    void disconnect_user(Client_info &);
    void disconnect_user(int id);
    //	Receive connections from clients
    void accept_users();
};
