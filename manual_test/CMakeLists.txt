add_executable(tcp_client tcp_client.cpp)
add_executable(udp_client udp_client.cpp)
add_executable(server server.cpp)

target_link_libraries(udp_client client_impl)
target_link_libraries(tcp_client client_impl)
target_link_libraries(server server_impl tcp_connection)
