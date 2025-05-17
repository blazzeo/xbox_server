#pragma once
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

using boost::asio::ip::tcp;

class TCP_Client {
  private:
    const std::string m_name{"tcp_client"};
    bool is_active{false};
    tcp::socket m_host_socket;
    tcp::resolver::results_type m_endpoints;

  public:
    TCP_Client(const std::string p_name, boost::asio::io_context &io_context,
               tcp::resolver::results_type &&endpoints)
        : m_name(p_name), m_host_socket(io_context), m_endpoints(endpoints) {}

    ~TCP_Client() = default;

    //	Methods
    auto start() -> void;
    auto stop() -> void;
    auto send(std::string_view) -> void;
    auto read(std::string &) -> void;
    auto listen_broadcast() -> void;
};
