#include "client_impl.h"
#include "server_impl.h"
#include "gtest/gtest.h"
#include <boost/asio.hpp>
#include <boost/asio/ip/detail/endpoint.hpp>
#include <boost/asio/placeholders.hpp>

TEST(TEST_CONNECT, connection) { EXPECT_EQ(100, 50 + 50); }
