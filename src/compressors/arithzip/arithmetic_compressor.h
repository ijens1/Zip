#ifndef ARITHMETIC_COMPRESSOR_H
#define ARITHMETIC_COMPRESSOR_H

#include "data_compressor.h"

namespace arithzip {

  class ArithmeticCompressor : public zip::DataCompressor {
    zip::Model model;
    std::string compressor_state = "";

    unsigned long long int high = 0xffffffff, low = 0;
    const unsigned long long int state_mask = 0xffffffff;
    const unsigned long long int full_range = 0x100000000;
    const unsigned long long int half_range = 0x80000000;
    const unsigned long long int quarter_range = 0x40000000;
    const unsigned long long int minimum_range = 0x40000002;

    // Number of times we've expanded symmetrically about half_range
    unsigned long long int num_underflow_bits = 0;

    std::string doGetState() const override;
    double doGetPercentComplete() const override;
    void doSetModel(zip::Model) override;
    void doCompressFile(std::istream&, std::ostream&) override;

    void update(int, std::string&);
  };

}


#endif
