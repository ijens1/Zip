#ifndef ARITHMETIC_DECOMPRESSOR_H
#define ARITHMETIC_DECOMPRESSOR_H

#include <fstream>
#include "data_decompressor.h"
#include "bit_io.h"
#include "model.h"

namespace arithunzip {

  class ArithmeticDecompressor : public zip::DataDecompressor {
    std::string decompressor_state = "";

    unsigned long long int high = 0xffffffff, low = 0, code = 0;
    const unsigned long long int state_mask = 0xffffffff;
    const unsigned long long int full_range = 0x100000000;
    const unsigned long long int half_range = 0x80000000;
    const unsigned long long int quarter_range = 0x40000000;
    const unsigned long long int minimum_range = 0x40000002;

    std::string doGetState() const override;
    double doGetPercentComplete() const override;
    void doDecompressFile(std::string, std::string) override;

    void update(int, zip::Model&, zip::BitIn&, std::ifstream&);
  };

}


#endif
