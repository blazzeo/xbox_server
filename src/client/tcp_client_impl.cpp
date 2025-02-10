#include "tcp_client_impl.h"
#include <boost/asio/buffer.hpp>
#include <string_view>
#include <unistd.h>

template <class... Types>
std::string_view TCP_Client<Types...>::get_name() const {
    return m_name;
}

template <class... Types>
void TCP_Client<Types...>::bind(std::function<void(Types... args)> p_func) {
    m_func = p_func;
}

template <class... Types> void TCP_Client<Types...>::run() {
    is_active = true;
    for (;;) {
        auto it = boost::asio::buffer({1, 2, 3});
        m_host_socket.write_some(it);
        sleep(1000);
    }
}

template <class... Types> void TCP_Client<Types...>::stop() {
    is_active = false;
}
