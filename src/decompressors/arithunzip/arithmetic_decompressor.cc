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

void arithunzip::ArithmeticDecompressor::doDecompressFile(std::string file_name) {
  std::string file_extension = file_name.substr(file_name.find('.'));

  std::string file_core = file_name.substr(0, file_name.find('.'));
  // Decompress to current dir
  if (file_core.find('/') != std::string::npos) file_core = file_core.substr(file_core.rfind('/') + 1);

  std::ifstream fin{file_name, std::ios::binary | std::ios::in};
  zip::BitIn bin;

  decompressor_state = "Checking magic number...";
  notifyAllObservers();

  char c;
  std::string magic_number_str;
  for (size_t i = 0; i < zip::arithmetic_magic_number_str.length(); ++i) {
    fin.get(c);
    magic_number_str += c;
  }
  if (magic_number_str != zip::arithmetic_magic_number_str) {
    throw zip::ZipException{"ERROR: The provided .az file is corrupted\nTerminating..."};
  }

  unsigned char original_file_extension_length = 0;

  decompressor_state = "Retrieving original file extension...";
  notifyAllObservers();
  fin >> original_file_extension_length;

  std::string original_file_extension;

  for (int i = 0; i < original_file_extension_length; ++i) {
    fin.get(c);
    original_file_extension += c;
  }

  decompressor_state = "Retrieving original static model...";
  notifyAllObservers();

  unsigned int num_chars = 0;
  c = 0;
  unsigned long long c_occurences = 0;
  std::map<char, unsigned long long> occurences;

  fin >> num_chars;
  for (unsigned int i = 0; i < num_chars; ++i) {
    fin.get(c);
    fin >> c_occurences;
    occurences[c] = c_occurences;
  }

  zip::Model model{occurences};

  std::ofstream fout{file_core + "." + original_file_extension};
  std::string decompressed_output;
  unsigned long long int high = 0xffffffff, low = 0, state_mask = high, quarter_range = 0x40000000;
  unsigned int code = 0;
  unsigned char next_bit = 0;

  decompressor_state = "Decompressing file...";
  notifyAllObservers();

  // Read in initial 32 bits
  for (int i = 0; i < 32; ++i) {
    bin.pullBit(next_bit, fin);
    code = (code << 1) | next_bit;
  }

  while (true) {
    unsigned long long int range = high - low + 1;
    unsigned long long int offset = code - low;
    // Express offset as a cumulative occurence count
    unsigned long long int count = ((offset + 1) * model.getTotalOccurences() - 1) / range;
    char next_char = model.getChar(count);

    if (next_char == char(256)) {
      break;
    }
    fout << next_char;
    std::cout << "Value as percent of current range: " << double(offset) / range << " translates to count: " << count << " = " << model.getTotalOccurences() << " * " << double(offset) / range << std::endl;
    std::cout << "Outputting char: " << next_char << std::endl;
    zip::Range r = model.getRange(next_char);
    // Update high and low to range values of the char we just outputted
    high = low + r.high * range / r.denominator - 1;
    low = low + r.low * range / r.denominator;
    while (true) {
      std::cout << "low is at " << double(low) / 0xffffffff << " high is at " << double(high) / 0xffffffff << std::endl;
      // If the top two bits of high and low are same, move them out and read
      // in next bit for code
      if (high < 0x80000000 || low >= 0x80000000) {
        std::cout << "Discarding top bits..." << std::endl;
        high = ((high << 1) & state_mask) | 1;
        low = (low << 1) & state_mask;
        bin.pullBit(next_bit, fin);
        code = (code << 1) | next_bit;

      // If we are converging to 0x80000000, symmetrically expand around
      // 0x80000000
      } else if (low >= 0x40000000 && high < 0xc0000000) {
        std::cout << "Expanding symmetrically about half..." << std::endl;
        high = (((high - quarter_range) << 1) & state_mask) | 1;
        low = ((low - quarter_range) << 1) & state_mask;
        bin.pullBit(next_bit, fin);
        code = ((code - quarter_range) << 1) | next_bit;
      } else {
        break;
      }
    }
  }
}
