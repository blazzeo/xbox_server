# CMake generated Testfile for 
# Source directory: /Users/blazzeo/projects/xbox_server/tests
# Build directory: /Users/blazzeo/projects/xbox_server/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[MyTest]=] "/Users/blazzeo/projects/xbox_server/tests/my_test")
set_tests_properties([=[MyTest]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/blazzeo/projects/xbox_server/tests/CMakeLists.txt;19;add_test;/Users/blazzeo/projects/xbox_server/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
