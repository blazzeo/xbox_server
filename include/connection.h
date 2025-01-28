#pragma once
#include <boost/asio.hpp>
#include <memory>

using boost::asio::ip::tcp;

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
    tcp::socket socket_;
    std::string message_;

    tcp_connection(boost::asio::io_context &io_context) : socket_(io_context) {}

    void write();
    void read();

  public:
};
