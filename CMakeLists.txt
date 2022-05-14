cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)

PROJECT(RShell)

#Uncomment this for Hammer development
#INCLUDE_DIRECTORIES(/usr/include/boost/)

#Uncomment this for Mac development
FIND_PACKAGE(Boost COMPONENTS tokenizer.hpp)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(test
        unit_tests/main.cpp
        unit_tests/parser_tests.cpp
        unit_tests/singlecommands_tests.cpp
        unit_tests/operators_tests.cpp
        src/operators.cpp
        unit_tests/testcommand_tests.cpp
        src/testcommand.hpp
        src/testcommand.cpp)

ADD_EXECUTABLE(rshell
        src/main.cpp
        src/parser.hpp
        src/parser.cpp
        src/commands.hpp
        src/singlecommand.hpp
        src/singlecommand.cpp
        src/base.hpp
        src/operators.hpp
        src/operators.cpp
        src/andconnector.hpp
        src/orconnector.hpp
        src/testcommand.hpp
        src/testcommand.cpp)


TARGET_LINK_LIBRARIES(rshell ${Boost_TOKENIZER_LIBRARY})
TARGET_LINK_LIBRARIES(test gtest)
TARGET_LINK_LIBRARIES(test ${Boost_TOKENIZER_LIBRARY})
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)

ADD_SUBDIRECTORY(googletest)

