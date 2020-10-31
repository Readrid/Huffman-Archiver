#include <set>

#include "Huffman.h"

HuffmanTree::HuffmanNode::HuffmanNode(int w, char lit) noexcept : weight(w), letter(lit) {}

bool HuffmanTree::HuffmanNode::operator<(const HuffmanNode &other) const noexcept {
    if (weight == other.weight) {
        return letter < other.letter;
    }
    return weight < other.weight;
}

HuffmanTree::HuffmanTree(const std::unordered_map<char, int32_t> &weightTable) : codeTable(CHAR_MAX) {

    auto compare = [](const std::unique_ptr<HuffmanNode>& a, const std::unique_ptr<HuffmanNode>& b) {
        return *a < *b;
    };
    std::multiset<std::unique_ptr<HuffmanNode>, decltype(compare)> buildHelper(compare);
    std::unique_ptr<HuffmanNode> tmpNode, tmpNode1, tmpNode2;

    for (auto chInfo : weightTable) {
        buildHelper.insert(std::make_unique<HuffmanNode>(chInfo.second, chInfo.first));
    }

    if (buildHelper.size() == 1) {
        root = std::move(buildHelper.extract(buildHelper.begin()).value());
        cur_pos = root.get();
        codeTable[root->letter] = "0";
        return;
    }

    while (buildHelper.size() > 1) {
        tmpNode1 = std::move(buildHelper.extract(buildHelper.begin()).value());
        tmpNode2 = std::move(buildHelper.extract(buildHelper.begin()).value());

        tmpNode = std::make_unique<HuffmanNode>(tmpNode1->weight + tmpNode2->weight);
        tmpNode->left = std::move(tmpNode1);
        tmpNode->right = std::move(tmpNode2);

        buildHelper.insert(std::move(tmpNode));
    }

    root = std::move(buildHelper.extract(buildHelper.begin()).value());
    cur_pos = root.get();

    createCodesTable(root);
}

void HuffmanTree::createCodesTable(const std::unique_ptr<HuffmanNode>& node) noexcept {
    if (!node->left && !node->right) {
        codeTable[node->letter] = codesBuf;
        return;
    }

    codesBuf += "0";
    createCodesTable(node->left);
    codesBuf.pop_back();

    codesBuf += "1";
    createCodesTable(node->right);
    codesBuf.pop_back();
}

bool HuffmanTree::isCurLeaf() {
    return !cur_pos->left && !cur_pos->right;
}

void HuffmanTree::move(char direction) {
    if (isCurLeaf()) return;
    if (direction == '0') {
        cur_pos = cur_pos->left.get();
    } else {
        cur_pos = cur_pos->right.get();
    }
}

char HuffmanTree::getCharAndDrop() {
    char tmp = cur_pos->letter;
    cur_pos = root.get();
    return tmp;
}

const std::string& HuffmanTree::getCode(char character) const {
    return codeTable[character];
}
