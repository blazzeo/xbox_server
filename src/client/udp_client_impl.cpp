#include "udp_client_impl.h"
#include <format>

void UDP_Client::send(const std::string &msg) {
    if (msg.empty())
        return;

    m_socket.send_to(boost::asio::buffer(std::format("[{}] {}", m_name, msg)),
                     m_endpoints);
}

std::string UDP_Client::recv() {
    char recv_msg[128];
    boost::asio::ip::udp::endpoint sender_endpoint;
    m_socket.receive_from(boost::asio::buffer(recv_msg), sender_endpoint);

    return std::string(recv_msg);
}
