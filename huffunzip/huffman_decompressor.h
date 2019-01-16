#ifndef HUFFMAN_DECOMPRESSOR_H
#define HUFFMAN_DECOMPRESSOR_H

#include <fstream>
#include <memory>
#include "data_decompressor.h"

namespace zip { class HuffmanNode; }

namespace huffunzip {

  class HuffmanDecompressor : public DataDecompressor {
      std::string decompressor_state = "";

      std::string doGetState() const override;
      double doGetPercentComplete() const override;
      void doDecompressFile(std::string) override;

      unsigned long long retrieveUncompressedFileLength(std::istream&);
      std::unique_ptr<zip::HuffmanNode> generateEncodingTree(std::istream&);
  };

}

#endif
