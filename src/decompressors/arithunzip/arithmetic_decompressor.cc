#include <bitset>
#include <map>
#include "arithmetic_decompressor.h"
#include "zip_exception.h"

std::string arithunzip::ArithmeticDecompressor::doGetState() const {
  return decompressor_state;
}

double arithunzip::ArithmeticDecompressor::doGetPercentComplete() const {
  return 0;
}

void arithunzip::ArithmeticDecompressor::doDecompressFile(std::string in_file_name, std::string out_file_name) {
    std::ifstream fin{in_file_name};
    std::ofstream fout{out_file_name};
    zip::BitIn bin;
    std::map<int, int> occurences;

    // Read in the model
    for (int i = 0; i < 256; ++i) {
        int occurence = 0;
        for (int j = 0; j < 32; ++j) {
          unsigned char next_bit = 0;
          bin.pullBit(next_bit, fin);
          occurence = (occurence << 1) | next_bit;
        }
        occurences[i] = occurence;
    }
    // EOF symbol
    occurences[256] = 1;

    zip::Model model{occurences};

    // Fill the code with the initial 32 bits
    for (int i = 0; i < 32; ++i) {
      unsigned char next_bit = 0;
      bin.pullBit(next_bit, fin);
      code = (code << 1) | next_bit;
    }

    while (true) {
      unsigned int total = model.getTotalOccurences();
      unsigned long long int range = high - low + 1;
      unsigned long long int code_offset = code - low;
      int position = ((code_offset + 1) * total - 1) / range;
      if (position * range / total > code_offset) {
        throw zip::ZipException{"Assertion error: Back check on position calculation incorrect"};
      }
      if (position >= total) {
        throw zip::ZipException{"Assertion error: position is greater than or equal to total occurences"};
      }

      int character = model.getCharacter(position);
      std::pair<int, int> character_range = model.getRange(character);
      if (code_offset < character_range.first * range / total || character_range.second * range / total <= code_offset) {
        throw zip::ZipException{"Assertion error: The character range does not contain the computed offset. The character selection based on position was incorrect"};
      }

      update(character, model, bin, fin);

      if (code < low || code > high) {
        throw zip::ZipException{"Assertion error: The character is no longer in the correct range after update"};
      }

      // We've reached the end of the code
      if (character == 256) {
        break;
      }
      fout << char(character);
    }
}

void arithunzip::ArithmeticDecompressor::update(int next_char, zip::Model& model, zip::BitIn& bin, std::ifstream& fin) {
    if (low >= high || (low & state_mask) != low || (high & state_mask) != high) {
      throw zip::ZipException{"Assertiion failed. Either low is geq high or low or high is not in the correct 32 bit range"};
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
      unsigned char c;
      bin.pullBit(c, fin);
      code = ((code << 1) & state_mask) | c;
      // These are simplifications of conceptual idea of expanding
      // the upper or lower half by a factor of two
      low = ((low << 1) & state_mask);
      high = ((high << 1) & state_mask) | 1;
    }

    // Prevent underflow from converging around half_range
    while (low >= quarter_range && high < quarter_range + half_range) {
      unsigned char c;
      bin.pullBit(c, fin);
      // Remove the second bit and pull in next bit
      code = (code & half_range) | ((code << 1) & (state_mask >> 1)) | c;
      low = (low << 1) & half_range;
      high = ((high << 1) | half_range) | 1;
    }
}
