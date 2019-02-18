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
  unsigned int high = 0xffffffff;
  unsigned int low = 0;

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

  compressor_state = "Writing model...";
  notifyAllObservers();

  fout << model.getNumElements();
  for (auto c : model) {
    fout << c.first << c.second;
  }

  // Stores the number of opposite bits that need to be outputted after
  // symmetrically expanding the interval [0.25, 0.75) num_pending_bits number of
  // times
  unsigned int num_pending_bits = 0;

  compressor_state = "Compressing file...";
  notifyAllObservers();

  while (fin.get(next_char)) {
    std::cout << "Reading in \'" << next_char << "\'..." << std::endl;
    unsigned int range = high - low;
    zip::Range char_range = model.getRange(next_char);
    high = low + range * (double(char_range.high) / char_range.denominator);

    // Need to add ceil here since we need still need to handle result as
    // though range was infinite
    low = low + std::ceil(range * (double(char_range.low) / char_range.denominator));

    // Move out as many bits as possible
    while (true) {
      std::cout << "low is at " << (double(low) / 4294967296) * 100 << "\% high is at " << (double(high) / 4294967296) * 100 << "\%" << std::endl;
      // If we know it will always be below half
      if (high < 0x80000000) {
        std::cout << "Expanding lower half..." << std::endl;
        // Multiply both numbers by two and output 0
        bin_output.push_back('0');
        high <<= 1;
        high |= 1;
        low <<= 1;
        // Output any pending bits
        outputPendingBits(num_pending_bits, false, bin_output);

      // If we know it will always be above half
      } else if (low >= 0x80000000) {
        std::cout << "Expanding upper half..." << std::endl;
        // Substract 0x80000000 from both, multiply by two, and output 1
        bin_output.push_back('1');
        high -= 0x80000000;
        low -= 0x80000000;
        high <<= 1;
        high |= 1;
        low <<= 1;
        // Output any pending bits
        outputPendingBits(num_pending_bits, true, bin_output);

      // Prevent convergence around 0x80000000
      } else if (low >= 0x40000000 && high < 0xc0000000) {
        std::cout << "Expanding middle..." << std::endl;
        // Subtract 0x40000000 from both, multiple by 2, increment num_pending_bits
        ++num_pending_bits;
        high -= 0x40000000;
        low -= 0x40000000;
        high <<= 1;
        high |= 1;
        low <<= 1;
      } else {
        break;
      }
    }
  }

  // Now just output low
  while (low != 0) {
    if (low >= 0x80000000) {
      bin_output.push_back('1');
      low -= 0x80000000;
      low <<= 1;

      outputPendingBits(num_pending_bits, true, bin_output);
    } else {
      bin_output.push_back('0');
      low <<= 1;

      outputPendingBits(num_pending_bits, false, bin_output);
    }
  }

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
