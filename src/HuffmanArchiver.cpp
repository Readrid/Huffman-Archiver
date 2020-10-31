#include "HuffmanArchiver.h"
#include "bin_manip.h"


HuffmanArchiver::HuffmanArchiver(std::istream &new_in, std::ostream &new_out) : in(new_in), out(new_out),
                                                                                freqTable(CHAR_MAX) {}

void HuffmanArchiver::bitesEncode(const HuffmanTree& tree) {
    char ch;
    unsigned char bitesBuf = 0;
    std::string code;
    unsigned int it = 0;
    while (in.read(&ch, 1)) {
        code = tree.getCode(ch);
        for (char bit : code) {
            if (bit == '1') {
                bitesBuf |= 1u << it;
            }
            it++;
            if (it == BYTE_SIZE) {
                it = 0;
                out.write(reinterpret_cast<char*>(&bitesBuf), 1);
                bitesBuf = 0;
            }
        }
    }
    if (it > 0 && it < BYTE_SIZE) {
        out.write(reinterpret_cast<char*>(&bitesBuf), 1);
    }
}

void HuffmanArchiver::bitesDecode(HuffmanTree& tree) {
    unsigned char bitesBuf;
    std::string tmp;
    while (in.read(reinterpret_cast<char*>(&bitesBuf), 1)) {
        for (int i = 0; i < BYTE_SIZE; i++) {
            char bite = (bitesBuf >> i & 1u) + '0';
            tree.move(bite);
            if (tree.isCurLeaf()) {
                char curCh = tree.getCharAndDrop();
                if (--freqTable[curCh] < 0) continue;
                out.write(&curCh, 1);
            }
        }
    }
}

void HuffmanArchiver::compress() {

    if(in.peek() == EOF) {
        return;
    }

    char ch = 0;
    int alphabetSize = 0;
    while (in.read(&ch, 1)) {
        if (freqTable[ch] == 0) alphabetSize++;
        freqTable[ch]++;
    }

    out << write_le_int32(alphabetSize);

    for (auto chInfo : freqTable) {
        out.write(&chInfo.first, 1);
        out << write_le_int32(chInfo.second);
    }

    extraDataSize = out.tellp();

    HuffmanTree tree(freqTable);

    in.clear();
    inputFileSize = in.tellg();
    in.seekg(std::ios_base::beg);

    bitesEncode(tree);


    outputFileSize = out.tellp();
    outputFileSize -= extraDataSize;

    in.clear();
}

void HuffmanArchiver::extract() {
    if(in.peek() == EOF) {
        return;
    }

    int alphabetSize;
    in >> read_le_int32(alphabetSize);

    char ch;
    for (int i = 0; i < alphabetSize; i++) {
        in.read(&ch, 1);
        in >> read_le_int32(freqTable[ch]);
    }

    extraDataSize = in.tellg();

    HuffmanTree tree(freqTable);

    bitesDecode(tree);

    in.clear();
    inputFileSize = in.tellg();
    inputFileSize -= extraDataSize;
    outputFileSize = out.tellp();

}

void HuffmanArchiver::printInfo() noexcept {
    std::cout << "Input file size: " << inputFileSize << " bytes\n";
    std::cout << "Output file size " << outputFileSize << " bytes\n";
    std::cout << "Additional data size: "<< extraDataSize << " bytes\n";
}
