#include <iostream>
#include <fstream>
#include <cmath>
#include "arithmetic_compressor.h"
#include "zip_exception.h"
#include "model.h"
#include "bit_io.h"
#include "arithmetic_representation.h"

std::string arithzip::ArithmeticCompressor::doGetState() const {
  return compressor_state;
}

double arithzip::ArithmeticCompressor::doGetPercentComplete() const {
  return 0;
}

void arithzip::ArithmeticCompressor::doSetModel(zip::Model model) {
  this->model = model;
}

void arithzip::ArithmeticCompressor::doCompressFile(std::string file_name) {
}
