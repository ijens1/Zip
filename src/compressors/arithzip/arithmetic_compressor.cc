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

void arithzip::ArithmeticCompressor::doCompressFile(std::string in_file_name, std::string out_file_name) {
  std::string bin_out = "";

  // Write the model
  for (int i = 0; i < 256; ++i) {
    std::pair<int, int> range = model.getRange(i);
    for (int j = 31; j >= 0; --j) {
      bin_out.push_back(char((((range.second - range.first) >> j) & 1) + 48));
    }
  }

  std::ifstream fin{in_file_name};

  char next_char;
  while (fin.get(next_char)) {
    update(next_char, bin_out);
  }
  update(256, bin_out);
  bin_out += '1';

  std::ofstream fout{out_file_name};
  zip::BitOut().putBin(bin_out, fout);
}

void arithzip::ArithmeticCompressor::update(int next_char, std::string& bin_out) {
    if (low >= high || (low & state_mask) != low || (high & state_mask) != high) {
      throw zip::ZipException{"Assertiion failed. Either low is geq high or low or high is not in the correct 32 bit range. high: " + std::to_string(high) + " low: " + std::to_string(low)};
    }
    unsigned long long int curr_range = high - low + 1;
    if (curr_range < minimum_range || curr_range > full_range) {
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
      bin_out.push_back(out_bit);
      for (; num_underflow_bits > 0; --num_underflow_bits) {
        bin_out.push_back((out_bit == '1') ? '0' : '1');
      }
      // These are simplifications of conceptual idea of expanding
      // the upper or lower half by a factor of two
      low = ((low << 1) & state_mask);
      high = ((high << 1) & state_mask) | 1;
    }

    // Prevent underflow from converging around half_range
    while (low >= quarter_range && high < quarter_range + half_range) {
      ++num_underflow_bits;
      low = (low << 1) & (state_mask >> 1);
      high = (((high << 1) & state_mask) | half_range) | 1;
    }
}
