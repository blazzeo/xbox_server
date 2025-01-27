#include "client_impl.h"
#include <string_view>

int Client::get_id() const { return id; }

std::string_view Client::get_name() const { return name; }
