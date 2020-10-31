#include "Huffman.h"
#include "doctest.h"

TEST_CASE("One character") {
    std::unordered_map<char, int> freq;
    freq['a'] = 5;
    HuffmanTree tree(freq);
    CHECK(tree.getCode('a') == "0");
}

TEST_CASE("Characters from contest") {
    std::unordered_map<char, int> freq;
    freq['a'] = 4;
    freq['b'] = 2;
    freq['c'] = 1;
    freq['d'] = 1;
    HuffmanTree tree(freq);
    CHECK(tree.getCode('a') == "1");
    CHECK(tree.getCode('b') == "01");
    CHECK(tree.getCode('c') == "000");
    CHECK(tree.getCode('d') == "001");
}

TEST_CASE("Same frequency") {
    std::unordered_map<char, int> freq;
    freq['1'] = 2;
    freq['2'] = 2;
    freq['3'] = 2;
    freq['4'] = 2;
    HuffmanTree tree(freq);
    CHECK(tree.getCode('1') == "00");
    CHECK(tree.getCode('2') == "01");
    CHECK(tree.getCode('3') == "10");
    CHECK(tree.getCode('4') == "11");
}

TEST_CASE("Fibonacci sequence: the beginning") {
    std::unordered_map<char, int> freq;
    freq['1'] = 1;
    freq['2'] = 1;
    freq['3'] = 2;
    freq['4'] = 3;
    HuffmanTree tree(freq);
    CHECK(tree.getCode('1') == "100");
    CHECK(tree.getCode('2') == "101");
    CHECK(tree.getCode('3') == "11");
    CHECK(tree.getCode('4') == "0");
}
