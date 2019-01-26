#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include <queue>
#include <vector>
#include <memory>
#include "data_compressor.h"

namespace zip { class HuffmanNode; }

namespace huffzip {

  class HuffmanCompressor : public zip::DataCompressor {
      std::map<char, double> pmf;
      std::string compressor_state = "";
      unsigned long long current_byte = 0;

      std::string doGetState() const override;
      double doGetPercentComplete() const override;
      void doSetProbabilityMassFunction(std::map<char, double>) override;
      void doCompressFile(std::string) override;

      void determineEncodings(std::map<char, std::string>&, const zip::HuffmanNode* const, std::string)const;
      void generateCompressedTree(const zip::HuffmanNode *const, std::string&) const;
      void outputBinStrAsBin(const std::string&, std::ofstream&) const;
  };

}


#endif
