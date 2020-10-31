#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <memory>
#include <unordered_map>
#include <string>

template<typename T> using CurNode = T*;

constexpr int CHAR_MAX = 256;

class HuffmanTree {
public:
    HuffmanTree(const std::unordered_map<char, int32_t> &weightTable);

    const std::string& getCode(char character) const;
    char getCharAndDrop();

    void move(char direction);
    bool isCurLeaf();

private:
    struct HuffmanNode {
        int weight;
        char letter;
        std::unique_ptr<HuffmanNode> left = nullptr;
        std::unique_ptr<HuffmanNode> right = nullptr;

        HuffmanNode(int w, char lit = 0) noexcept;
        bool operator<(const HuffmanNode& other) const noexcept ;
    };

    std::unique_ptr<HuffmanNode> root;
    CurNode<HuffmanNode> cur_pos;
    std::string codesBuf;
    mutable std::unordered_map<char, std::string> codeTable;

    void createCodesTable(const std::unique_ptr<HuffmanNode>& node) noexcept ;
};

#endif
