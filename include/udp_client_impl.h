#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include <string>

using boost::asio::ip::udp;
class UDP_Client {
  private:
    std::string m_name{"udp_client"};
    udp::socket m_socket;
    udp::endpoint m_endpoints;

  public:
    UDP_Client(std::string &p_name, boost::asio::io_context &io_context,
               udp::endpoint &p_endpoint)
        : m_name(std::move(p_name)), m_socket(io_context),
          m_endpoints(p_endpoint) {
        m_socket.open(udp::v4());
    };

    ~UDP_Client() = default;

    void send(const std::string &);
    std::string recv();
};
