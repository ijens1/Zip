#include "arithmetic_decompressor.h"

std::string arithunzip::ArithmeticDecompressor::doGetState() const {
  return decompressor_state;
}

double arithunzip::ArithmeticDecompressor::doGetPercentComplete() const {
  return 0;
}

void arithunzip::ArithmeticDecompressor::doDecompressFile(std::string file_name) {
  // Read in the pmf
  // Read in the final fraction determined from encoding
  // Descend intervals, outputting the character that corresponds to that
  // interval as you go down.
  // Will probably use some kind of end of data symbol to encode end, unless
  // some other more convenient method comes up while actually writing it.
}
