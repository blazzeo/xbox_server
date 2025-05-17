#pragma once
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

struct TCP_connection {
    const int id;
    std::string name;
    tcp::socket socket;
    std::unique_ptr<std::thread> client_connection;

    TCP_connection(int id, std::string name, tcp::socket &&client_socket);
    ~TCP_connection();

    TCP_connection(const TCP_connection &other) = delete;
    TCP_connection &operator=(const TCP_connection &other) = delete;

    bool operator==(const TCP_connection &other);
    bool operator==(int other_id);

    friend std::ostream &operator<<(std::ostream &os,
                                    const TCP_connection &client);
};
