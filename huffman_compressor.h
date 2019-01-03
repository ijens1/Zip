#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include <queue>
#include <vector>
#include <memory>
#include "data_compressor.h"

namespace huffzip {

  struct HuffmanNode {
      char c;
      double prob;
      HuffmanNode *lchild = nullptr, *rchild = nullptr;

      HuffmanNode() = default;
      HuffmanNode(char c, double prob, HuffmanNode *lchild, HuffmanNode *rchild) : c{c}, prob{prob}, lchild{lchild}, rchild{rchild} {}
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

  class HuffmanCompressor : public DataCompressor {
      std::map<char, double> pmf;
      std::string compression_state = "";
      unsigned long long current_byte = 0;

      std::string doGetCompressorState() const override;
      double doGetPercentComplete() const override;
      void doSetProbabilityMassFunction(std::map<char, double>) override;
      void doCompressFile(std::string) override;

      void determineEncodings(std::map<char, std::string>&, HuffmanNode*, std::string);
  };

}


#endif
