#pragma once
#include "tcp_connection.h"
#include <atomic>
#include <cstdio>
#include <dbg.h>
#include <list>
#include <memory>
#include <string>
#include <thread>

class Server {
    size_t clients_count{0};
    std::list<TCP_connection> clients_pool;
    std::atomic<bool> is_available{false};
    tcp::acceptor m_acceptor;
    boost::asio::io_context &io_context;
    std::thread accept_thread;
    std::thread udp_thread;
    boost::asio::ip::udp::socket udp_socket;

  public:
    //	io_context, port
    Server(boost::asio::io_context &io_context, short port)
        : io_context(io_context),
          m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
          udp_socket(io_context) {
        udp_socket.open(boost::asio::ip::udp::v4());
        accept_thread = std::thread([this]() { accept_users(); });
        udp_thread = std::thread([this]() { accept_udp(); });
    }

    ~Server() {
        is_available = 0;
        if (accept_thread.joinable())
            accept_thread.join();

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
    void broadcast_echo(std::string);
    //	Block user
    void disconnect_user(int);
    //	Receive connections from clients
    void accept_users();
    //	Receive udp messages
    void accept_udp();
};
