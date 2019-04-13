#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include <queue>
#include <vector>
#include <memory>
#include "data_compressor.h"

namespace zip { struct HuffmanNode; }

namespace huffzip {

  class HuffmanCompressor : public zip::DataCompressor {
      zip::Model model;
      std::string compressor_state = "";
      unsigned long long current_byte = 0;

      std::string doGetState() const override;
      double doGetPercentComplete() const override;
      void doSetModel(zip::Model) override;
      void doCompressFile(std::istream&, std::ostream&) override;

      void determineEncodings(std::map<char, std::string>&, const zip::HuffmanNode* const, std::string)const;
      void generateCompressedTree(const zip::HuffmanNode *const, std::string&) const;
      void outputBinStrAsBin(const std::string&, std::ofstream&) const;
  };

}


#endif
