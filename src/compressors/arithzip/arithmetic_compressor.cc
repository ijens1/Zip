#include <iostream>
#include <fstream>
#include <limits>
#include "arithmetic_compressor.h"
#include "zip_exception.h"

std::string arithzip::ArithmeticCompressor::doGetState() const {
  return compressor_state;
}

double arithzip::ArithmeticCompressor::doGetPercentComplete() const {
  return 0;
}

void arithzip::ArithmeticCompressor::doSetProbabilityMassFunction(std::map<char, double> pmf) {
  this->pmf = pmf;
}

void arithzip::ArithmeticCompressor::doCompressFile(std::string file_name) {
  // for testing
  typedef std::numeric_limits<double> dbl;

  std::string file_core = file_name.substr(0, file_name.find('.'));

  // Compress to current dir
  if (file_core.find('/') != std::string::npos) file_core = file_core.substr(file_core.rfind('/') + 1);
  std::string file_extension = file_name.substr(file_name.find('.') + 1);

  // Go through and generate 'range minimum' for each character (i.e. value
  // where its interval begins)
  std::map<char, double> range_min;

  double curr_min = 0;
  for (auto& p : pmf) {
    range_min[p.first] = curr_min;
    curr_min += p.second;
  }

  for (auto& r : range_min) {
    std::cout << r.first << " has the range " << r.second << " to " << r.second + pmf[r.first] << std::endl;
  }

  // Reuse for encoding
  curr_min = 0;
  double curr_max = 1;

  std::ifstream fin{file_name};
  char next_char;
  std::cout.precision(dbl::max_digits10);
  while (fin >> next_char) {
    if (pmf.count(next_char) != 1) {
      std::string what = "No probability value found for character \'";
      what.push_back(next_char);
      what += "\'";
      throw zip::ZipException{what};
    }
    double next_min = ((curr_max - curr_min) * range_min[next_char]) + curr_min;
    double next_max = next_min + ((curr_max - curr_min) * pmf[next_char]);
    std::cout << "Descending to " << next_min << " to " << next_max << std::endl;
    curr_min = next_min;
    curr_max = next_max;
  }
}
