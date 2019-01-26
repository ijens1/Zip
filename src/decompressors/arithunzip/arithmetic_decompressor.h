#ifndef ARITHMETIC_DECOMPRESSOR_H
#define ARITHMETIC_DECOMPRESSOR_H

#include <fstream>
#include "data_decompressor.h"

namespace arithunzip {

  class ArithmeticDecompressor : public zip::DataDecompressor {
    std::string decompressor_state = "";

    std::string doGetState() const override;
    double doGetPercentComplete() const override;
    void doDecompressFile(std::string) override;
  };

}


#endif
