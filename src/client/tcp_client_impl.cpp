#include "tcp_client_impl.h"
#include "dbg.h"
#include <boost/asio/buffer.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <cstring>
#include <format>
#include <string_view>
#include <sys/socket.h>
#include <unistd.h>

auto TCP_Client::get_name() const -> std::string_view { return m_name; }

/*void TCP_Client::bind(std::function<void(Types... args)> p_func) {*/
/*    m_func = p_func;*/
/*}*/

auto TCP_Client::start() -> void {
    try {
        boost::asio::connect(m_host_socket, m_endpoints);
        std::cout << "Connection succesfull\n";
        is_active = true;

        send(m_name + '0');

        std::string ans;
        read(ans);

        if (ans.starts_with("OK")) {
            dbg("Server accepted name.");
        } else {
            dbg("Server didn't accept name.");
        }
    } catch (std::exception &e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
    }
}

auto TCP_Client::run() -> void {
    auto msg_id{0u};
    for (;;) {
        if (!m_host_socket.is_open()) {
            std::cerr << "Error: Socket closed, stopping client.\n";
            break;
        }

        std::string msg = std::format("hello{}", ++msg_id);
        try {
            send(msg + '0');
        } catch (const boost::system::system_error &e) {
            std::cerr << "Write error: " << e.what() << std::endl;
            break;
        }

        std::cout << "Sent: " << msg << "\n";
        sleep(1);
    }

    m_host_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    m_host_socket.close();
}

void TCP_Client::send(std::string_view msg) {
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

void TCP_Client::read(std::string &dest) {
    using boost::asio::dynamic_buffer, boost::asio::read_until;

    dest.clear();

    try {
        if (m_host_socket.is_open())
            read_until(m_host_socket, dynamic_buffer(dest), '0');

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        m_host_socket.close();
    }
}

void TCP_Client::stop() { is_active = false; }
