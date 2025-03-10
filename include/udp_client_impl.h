#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include <string>

using boost::asio::ip::udp;
class UDP_Client {
  private:
    const std::string m_name{"upd_client"};
    const short m_host_port;
    udp::resolver::results_type m_endpoints;

  public:
    UDP_Client(std::string &&p_name, short p_port,
               udp::resolver::results_type &&p_endpoint)
        : m_name(std::move(p_name)), m_host_port(p_port),
          m_endpoints(std::move(p_endpoint)) {};

    ~UDP_Client() = default;

    void send() const;
    void stop();
};
