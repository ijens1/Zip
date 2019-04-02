#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <string>
#include <memory>

/**
 * This file stores information about how I've actually implemented encoding.
**/
namespace zip {

  static const std::string huffman_file_extension = ".hz";
  static const unsigned long long huffman_magic_number = 0x4849444a4c;
  static const std::string huffman_magic_number_str = "HIDJL";

  struct HuffmanNode {
      unsigned int c;
      double prob;
      HuffmanNode *lchild, *rchild;

      HuffmanNode() = default;
      HuffmanNode(unsigned int c, double prob, HuffmanNode *lchild, HuffmanNode *rchild) : c{c}, prob{prob}, lchild{std::move(lchild)}, rchild{std::move(rchild)} {}
      HuffmanNode(const HuffmanNode&) = default;
      HuffmanNode(HuffmanNode&&) = default;
      HuffmanNode& operator=(const HuffmanNode&) = default;
      HuffmanNode& operator=(HuffmanNode&&) = default;
      ~HuffmanNode() = default;
  };

  struct CompareHuffmanNode {
    bool operator()(const HuffmanNode* n1, const HuffmanNode* n2) {
      // return true if n1 is ordered before n2 (the top will now be smallest
      // prob)
      return n1->prob > n2->prob;
    }
  };

}

#endif
