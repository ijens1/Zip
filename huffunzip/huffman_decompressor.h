#ifndef HUFFMAN_DECOMPRESSOR_H
#define HUFFMAN_DECOMPRESSOR_H

#include "data_decompressor.h"

namespace huffunzip {

  class HuffmanDecompressor : public DataDecompressor {
      std::string decompressor_state = "";

      std::string doGetState() const override;
      double doGetPercentComplete() const override;
      void doDecompressFile(std::string) override;
  };

}

#endif
