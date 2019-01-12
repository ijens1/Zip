#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <string>

/**
 * This file stores information about how I've actually implemented encoding.
**/
namespace zip {

  static const std::string huffman_file_extension = ".hz";
  static const int magic_number = 0x49444a4c;
  static const std::string magic_number_str = "IDJL";

  struct HuffmanNode {
      unsigned int c;
      double prob;
      HuffmanNode *lchild = nullptr, *rchild = nullptr;

      HuffmanNode() = default;
      HuffmanNode(unsigned int c, double prob, HuffmanNode *lchild, HuffmanNode *rchild) : c{c}, prob{prob}, lchild{lchild}, rchild{rchild} {}
      HuffmanNode(HuffmanNode&) = default;
      HuffmanNode(HuffmanNode&&) = default;
      HuffmanNode& operator=(HuffmanNode&) = default;
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
