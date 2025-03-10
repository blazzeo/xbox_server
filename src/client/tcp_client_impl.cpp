#include "tcp_client_impl.h"
#include "dbg.h"
#include <boost/asio/buffer.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <cstring>
#include <exception>
#include <string_view>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

auto TCP_Client::start() -> void {
    try {
        boost::asio::connect(m_host_socket, m_endpoints);
        is_active = true;

        send(m_name + '\n');

        std::string ans;
        read(ans);

        if (not ans.starts_with("OK"))
            throw "server rejected name";

        std::cout << "Connected!\n";
    } catch (std::exception &e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
    }
}

auto TCP_Client::listen_broadcast() -> void {
    using boost::asio::async_read_until, boost::asio::dynamic_buffer;
    std::string msg;
    while (is_active) {
        auto len = async_read_until(m_host_socket, dynamic_buffer(msg), '\n');

        if (msg.length() > 0)
            std::cout << "Recv: " << msg << std::endl;
    }
}

auto TCP_Client::send(std::string_view msg) -> void {
    using boost::asio::buffer, boost::asio::write;
    if (msg.empty())
        return;

    try {
        if (m_host_socket.is_open())
            write(m_host_socket, buffer(msg));

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        m_host_socket.close();
    }
}

auto TCP_Client::read(std::string &dest) -> void {
    using boost::asio::dynamic_buffer, boost::asio::read_until;

    dest.clear();

    try {
        if (m_host_socket.is_open())
            read_until(m_host_socket, dynamic_buffer(dest), '\n');

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        m_host_socket.close();
    }
}

auto TCP_Client::stop() -> void {
    is_active = false;

    m_host_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    m_host_socket.close();
}
