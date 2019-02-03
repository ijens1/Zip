#include <iostream>
#include <fstream>
#include "arithmetic_compressor.h"
#include "zip_exception.h"

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
  std::string file_core = file_name.substr(0, file_name.find('.'));

  // Compress to current dir
  if (file_core.find('/') != std::string::npos) file_core = file_core.substr(file_core.rfind('/') + 1);
  std::string file_extension = file_name.substr(file_name.find('.') + 1);

  // Note that these numbers are mantissas (i.e. they have an implicit 0. in
  // front of them)
  unsigned int max = 0xffffffffu;
  unsigned int low = 0;

  std::ifstream fin{file_name};
  char next_char;
}
