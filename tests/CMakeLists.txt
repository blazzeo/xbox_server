project(server_testing)

enable_testing()

include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(my_test tests.cpp)
target_link_libraries(my_test PRIVATE gtest gtest_main server_impl client_impl)
set(CTEST_SOURCE_DIRECTORY build/tests/)

add_test(NAME MyTest COMMAND my_test)
