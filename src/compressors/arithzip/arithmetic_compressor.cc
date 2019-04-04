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
  std::string bin_out = ""

  // Write the model
  for (int i = 0; i < 256; ++i) {
    std::pair<int, int> range = model.getRange(i);
    for (int j = 31; j >= 0; --j) {
      bin_out.push_back(((range.second - range.first) >> j) & 1);
    }
  }

  std::ifstream fin{file_name};

  char next_char;
  while (fin.get(next_char)) {
    update(next_char);
  }
  update(256);
}

void arithzip::ArithmeticCompressor::update(int next_char) {
    if (low >= high || (low & state_mask) != low || (high & state) != high) {
      throw zip::ZipException{"Assertiion failed. Either low is geq high or low or high is not in the correct 32 bit range"};
    }
    unsigned long long int curr_range = high - low + 1;
    if (range < minimum_range || range > full_range) {
      throw zip::ZipException{"Assertion failed. Range is not an acceptable value"};
    }

    int total = model.getTotalOccurences();
    std::pair<int, int> character_range = model.getRange(next_char);
    if (character_range.first == character_range.second) {
      throw zip::ZipException{"Character has zero occurences"};
    }

    high = low + character_range.second * curr_range / total - 1;
    low = low + character_range.first * curr_range / total;

    // If low and high have the same top bit, they will always have the same
    // top bit, so shift it out
    while (((low ^ high) & half_range) == 0) {
      char out_bit = char((low >> 31) + 48);
      bin_out
    }
}
