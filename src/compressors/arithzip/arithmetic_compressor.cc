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
  std::string file_core = file_name.substr(0, file_name.find('.'));

  // Compress to current dir
  if (file_core.find('/') != std::string::npos) file_core = file_core.substr(file_core.rfind('/') + 1);
  std::string file_extension = file_name.substr(file_name.find('.') + 1);

  // Declare streams
  std::ifstream fin{file_name};
  std::ofstream fout{file_core + zip::arithmetic_file_extension};
  zip::BitOut bout;

  char next_char;
  std::string bin_output;

  compressor_state = "Writing magic number...";
  notifyAllObservers();

  fout << zip::arithmetic_magic_number_str;

  unsigned char file_extension_length = file_extension.length();

  compressor_state = "Writing file extension...";
  notifyAllObservers();

  fout << file_extension_length << file_extension;

  compressor_state = "Writing static model...";
  notifyAllObservers();

  fout << model.getNumElements();
  for (auto c : model) {
    fout << c.first << c.second;
  }

  compressor_state = "Compressing file...";
  notifyAllObservers();

  high = 0xffffffff;
  low = 0;
  num_pending_bits = 0;

  while (fin.get(next_char)) {
    update(next_char, bin_output);
  }
  // Write the EOF char
  update(char(256), bin_output);
  bin_output.push_back('1');

  compressor_state = "Outputting compressed data...";
  notifyAllObservers();

  // Output the encoded file
  bout.putBin(bin_output, fout);
}

void arithzip::ArithmeticCompressor::outputPendingBits(unsigned int& num_pending_bits, bool is_outputting_one, std::string& bin_output) {
  char opposite_bit = (is_outputting_one) ? '0' : '1';
  for (unsigned int i = 0; i < num_pending_bits; ++i) bin_output.push_back(opposite_bit);
  num_pending_bits = 0;
}

void arithzip::ArithmeticCompressor::update(char c, std::string& bin_output) {
  unsigned long long int range = high - low + 1;

  zip::Range char_range = model.getRange(c);
  high = low + range * char_range.high / char_range.denominator - 1;
  low = low + range * char_range.low / char_range.denominator;
  if ((high & state_mask) != high || (low & state_mask) != low) {
    std::cerr << "High or low has exceeded maxiumum value. Ending encoding." << std::endl;
    return;
  }

  // Move out as many bits as possible
  while (true) {
    // If we know it will always be below half
    if (high < 0x80000000) {
      // Multiply both numbers by two and output 0
      bin_output.push_back('0');
      high = ((high << 1) | 1) & state_mask;
      low = (low << 1) & state_mask;
      // Output any pending bits
      outputPendingBits(num_pending_bits, false, bin_output);

    // If we know it will always be above half
    } else if (low >= 0x80000000) {
      // Substract 0x80000000 from both, multiply by two, and output 1
      bin_output.push_back('1');
      high = ((high << 1) | 1) & state_mask;
      low = (low << 1) & state_mask;
      // Output any pending bits
      outputPendingBits(num_pending_bits, true, bin_output);

    // Prevent convergence around 0x80000000
    } else if (low >= 0x40000000 && high < 0xc0000000) {
      // Subtract 0x40000000 from both, multiple by 2, increment num_pending_bits
      ++num_pending_bits;
      high -= 0x40000000;
      low -= 0x40000000;
      high = ((high << 1) | 1) & state_mask;
      low = (low << 1) & state_mask;
    } else {
      break;
    }
  }
}
