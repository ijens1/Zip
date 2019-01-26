#ifndef ARITHMETIC_COMPRESSOR_H
#define ARITHMETIC_COMPRESSOR_H

#include "data_compressor.h"

namespace arithzip {

  class ArithmeticCompressor : public zip::DataCompressor {
    std::map<char, double> pmf;
    std::string compressor_state = "";

    std::string doGetState() const override;
    double doGetPercentComplete() const override;
    void doSetProbabilityMassFunction(std::map<char, double>) override;
    void doCompressFile(std::string) override;
  };

}


#endif
