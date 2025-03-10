add_library(server_impl server_impl.cpp)
add_library(tcp_connection tcp_connection.cpp)
target_link_libraries(server_impl Boost::iostreams)
target_link_libraries(tcp_connection Boost::iostreams)
