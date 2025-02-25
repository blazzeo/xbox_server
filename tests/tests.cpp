#include "server_impl.h"
#include "tcp_client_impl.h"
#include "gtest/gtest.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/detail/endpoint.hpp>
#include <boost/asio/placeholders.hpp>

TEST(CONNECTION_TESTS, tcp_connection) {
    boost::asio::io_context io_context;

    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoint{resolver.resolve("127.0.0.1", "5001")};

    auto server{Server(io_context, 5001)};
    auto client{TCP_Client("test", io_context, std::move(endpoint))};

    server.start();
    client.run();

    EXPECT_EQ(100, 50 + 50);
}
