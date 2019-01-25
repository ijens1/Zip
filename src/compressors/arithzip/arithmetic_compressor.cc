#include "arithmetic_compressor.h"

std::string arithzip::ArithmeticCompressor::doGetState() const {
  return compressor_state;
}

double arithzip::ArithmeticCompressor::doGetPercentComplete() const {
  return 0;
}

void arithzip::ArithmeticCompressor::doSetProbabilityMassFunction(std::map<char, double> pmf) {
  this->pmf = pmf;
}

void arithzip::doCompressFile(std::string file_name) {
  // Divide [0, 1) into subintervals based on pmf
  // Continue descending into intervals based on next character to be encoded
  // Return any fraction inside of the final interval (I'll most likely just
  // return the half way point)
}
