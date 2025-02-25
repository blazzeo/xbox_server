add_executable(client client.cpp)
add_executable(server server.cpp)

target_link_libraries(client client_impl)
target_link_libraries(server server_impl)
