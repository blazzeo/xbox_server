#pragma once
#include "boost/asio.hpp"
#include "connection.h"
#include <atomic>
#include <list>
#include <thread>

using boost::asio::ip::tcp;

struct Client_info {
    const int id;
    const std::string name;
    std::thread client_thread;
    tcp::socket socket;

    Client_info(int id, std::string name, tcp::socket &&client_socket)
        : id(id), name(name), socket(std::move(client_socket)),
          client_thread() {}

    ~Client_info() {
        if (client_thread.joinable())
            client_thread.join();
    }

    bool operator==(const Client_info &other) {
        return this->id == other.id and this->name == other.name;
    }

    bool operator==(int other_id) { return this->id == other_id; }
};

class Server {
    static size_t clients_count;
    std::list<Client_info> clients_pool;
    std::atomic<bool> is_available;
    tcp::acceptor acceptor_;
    boost::asio::io_context &io_context;

  public:
    Server(boost::asio::io_context &io_context,
           tcp::resolver::results_type endpoints, short port)
        : io_context(io_context),
          acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
          is_available(false), clients_pool({}) {
        clients_count = 0;
    }

    ~Server() {
        for (auto &client : clients_pool) {
            if (client.client_thread.joinable())
                client.client_thread.join();
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
