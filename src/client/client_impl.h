#pragma once
#include "boost/asio.hpp"
#include <string>
#include <utility>

class Client {
    int id;
    std::string name;
    int socket;

  public:
    Client(int id, std::string name, int socket)
        : id(id), name(std::move(name)), socket(socket) {}

    Client(const Client &other)
        : id(other.id), name(other.name), socket(other.socket) {}

    Client(Client &&other) noexcept
        : id(other.id), name(std::move(other.name)), socket(other.socket) {}

    Client &operator=(Client &&other) noexcept {
        if (this != &other) {
            id = other.id;
            name = std::move(other.name);
            socket = other.socket;
            other.socket = -1;
        }
        return *this;
    }

    Client &operator=(const Client &other) {
        if (this != &other) {
            this->id = other.id;
            this->name = other.name;
            this->socket = other.socket;
        }
        return *this;
    }

    ~Client() = default;

    //	Methods

    int get_id() const;
    std::string_view get_name() const;
};
