project(hw_03)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra")

add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE doctest)

add_executable(
        archiver
        src/main.cpp
        src/Huffman.cpp
        include/Huffman.h
        src/HuffmanArchiver.cpp
        include/HuffmanArchiver.h
        src/CLI.cpp
        include/CLI.h
        src/bin_manip.cpp
        include/bin_manip.h
)

target_link_libraries(archiver)

add_executable(
        test_archiver
        src/Huffman.cpp
        include/Huffman.h
        src/HuffmanArchiver.cpp
        include/HuffmanArchiver.h
        src/CLI.cpp
        include/CLI.h
        src/bin_manip.cpp
        include/bin_manip.h
        test/TestMain.cpp
        test/testHuffman.cpp
        test/testHuffmanArchiver.cpp
        test/testCLI.cpp
)

target_link_libraries(test_archiver doctest)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include_directories(include)
