#ifndef ARITHMETIC_COMPRESSOR_H
#define ARITHMETIC_COMPRESSOR_H

#include "data_compressor.h"

namespace arithzip {

  class ArithmeticCompressor : public zip::DataCompressor {
    zip::Model model;
    std::string compressor_state = "";

    std::string doGetState() const override;
    double doGetPercentComplete() const override;
    void doSetModel(zip::Model) override;
    void doCompressFile(std::string) override;

    void outputPendingBits(unsigned int&, bool, std::string&);
  };

}


#endif
