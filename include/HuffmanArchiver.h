#ifndef _HUFFMAN_ARCHIVER_H_
#define _HUFFMAN_ARCHIVER_H_

#include <iostream>

#include "Huffman.h"

constexpr int BYTE_SIZE = 8;

class HuffmanArchiver {
public:
    HuffmanArchiver(std::istream& new_in, std::ostream& new_out);

    void compress();
    void extract();

    void printInfo() noexcept;

private:
    void bitesEncode(const HuffmanTree& tree);
    void bitesDecode(HuffmanTree& tree);

    std::istream& in;
    std::ostream& out;
    std::unordered_map<char, int32_t> freqTable;
    size_t inputFileSize = 0;
    size_t extraDataSize = 0;
    size_t outputFileSize = 0;
};

#endif
