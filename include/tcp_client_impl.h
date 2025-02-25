#pragma once
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

// clang-format off
class TCP_Client {
  private:
    const std::string m_name{"default"};
    bool is_active{false};
    tcp::socket m_host_socket;

  public:
    TCP_Client(const std::string p_name, boost::asio::io_context &io_context,
               const tcp::resolver::results_type &endpoints)
        : m_name(p_name), m_host_socket(io_context) {
        try {
            boost::asio::connect(m_host_socket, endpoints);
            std::cout << "Connection succesfull\n";
        } catch (std::exception &e) {
            std::cerr << "Connection failed: " << e.what() << std::endl;
        }
    }

    ~TCP_Client() = default;

    //	Methods
    auto run() -> void;
    auto stop() -> void;
    auto get_name() const -> std::string_view;
	auto send(std::string_view) -> void;
	auto read(std::string &dest) -> void;
};
// clang-format on
