# CMake generated Testfile for 
# Source directory: C:/Medforge/Project-Athena
# Build directory: C:/Medforge/Project-Athena/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(care-pulse-self-tests "C:/Medforge/Project-Athena/build/care-pulse.exe" "--self-test")
set_tests_properties(care-pulse-self-tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Medforge/Project-Athena/CMakeLists.txt;33;add_test;C:/Medforge/Project-Athena/CMakeLists.txt;0;")
