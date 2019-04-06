#include <bitset>
#include <map>
#include "arithmetic_decompressor.h"
#include "arithmetic_representation.h"
#include "bit_io.h"
#include "zip_exception.h"
#include "model.h"

std::string arithunzip::ArithmeticDecompressor::doGetState() const {
  return decompressor_state;
}

double arithunzip::ArithmeticDecompressor::doGetPercentComplete() const {
  return 0;
}

void arithunzip::ArithmeticDecompressor::doDecompressFile(std::string in_file_name, std::string out_file_name) {

}
