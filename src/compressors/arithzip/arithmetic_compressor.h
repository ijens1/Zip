#ifndef ARITHMETIC_COMPRESSOR_H
#define ARITHMETIC_COMPRESSOR_H

#include "data_compressor.h"

namespace arithzip {

  class ArithmeticCompressor : public zip::DataCompressor {
    zip::Model model;
    std::string compressor_state = "";
    /**
     * Note that these numbers are mantissas (i.e. they have an implicit 0. in
     * front of them)
     * See the following paper on the use of integer arithmetic and its effects
     * on code length:
     * https://www.cc.gatech.edu/~jarek/courses/7491/Arithmetic2.pdf
     * Main highlight is that the use of integer math doesn't significantly
     * impact the final code length.
     * As far as I can tell, the main benefit of using integer math over
     * floating point math is that you can use bit operations, which are faster
     * than the multiplication operations that you would be doing with
     * doubles/floats.
     * You could probably represent the high and low using the floating point
     * representations in combination with the range checks to avoid high and low
     * to converging to the same value.
    **/
    unsigned long long int high = 0xffffffff, low = 0;

    // State mask to make sure that we continue to treat high and low as though
    // they were 32 bits
    const unsigned long long int state_mask = high;

    // Stores the number of opposite bits that need to be outputted after
    // symmetrically expanding the interval [0.25, 0.75) num_pending_bits number of
    // times
    unsigned int num_pending_bits = 0;

    std::string doGetState() const override;
    double doGetPercentComplete() const override;
    void doSetModel(zip::Model) override;
    void doCompressFile(std::string) override;

    void outputPendingBits(unsigned int&, bool, std::string&);
    void update(char c, std::string& bin_output);
  };

}


#endif
