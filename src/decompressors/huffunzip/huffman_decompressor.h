#ifndef HUFFMAN_DECOMPRESSOR_H
#define HUFFMAN_DECOMPRESSOR_H

#include <fstream>
#include <memory>
#include "data_decompressor.h"

namespace zip {
  struct HuffmanNode;
  class BitIn;
}

namespace huffunzip {

  class HuffmanDecompressor : public zip::DataDecompressor {
      std::string decompressor_state = "";

      std::string doGetState() const override;
      double doGetPercentComplete() const override;
      void doDecompressFile(std::istream&, std::ostream&) override;

      int retrieveUncompressedFileLength(std::istream&);
      void generateEncodingTree(std::istream&, std::vector<std::unique_ptr<zip::HuffmanNode>>&, zip::BitIn&, zip::HuffmanNode*&);
      char parseNextChar(std::istream&, zip::HuffmanNode*, zip::BitIn&);
  };

}

#endif
