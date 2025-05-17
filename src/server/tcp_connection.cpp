#include "tcp_connection.h"

TCP_connection::TCP_connection(int id, std::string name,
                               tcp::socket &&client_socket)
    : id(id), name(std::move(name)), socket(std::move(client_socket)),
      client_connection(std::make_unique<std::thread>([this]() {
          while (true) {
              std::string msg;
              boost::asio::read_until(socket, boost::asio::dynamic_buffer(msg),
                                      '\n');

              printf("[%s] : %s\n", this->name.c_str(), msg.c_str());

              boost::asio::write(socket, boost::asio::buffer("ECHO_" + msg));
          }
      })) {}

TCP_connection::~TCP_connection() {
    if (client_connection->joinable())
        client_connection->join();
}

bool TCP_connection::operator==(const TCP_connection &other) {
    return this->id == other.id and this->name == other.name;
}

bool TCP_connection::operator==(int other_id) { return this->id == other_id; }

std::ostream &operator<<(std::ostream &os, const TCP_connection &client) {
    return os << client.id << ' ' << client.name;
}
