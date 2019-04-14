#include <catch.hpp>
#include <sstream>
#include <fstream>
#include <bitset>
#include "bit_io.h"
#include "../../compressors/arithzip/arithmetic_compressor.h"
#include "../../decompressors/arithunzip/arithmetic_decompressor.h"

const std::string compressed_arithmetic_model_filename = "compressed_arithmetic_model.txt";

TEST_CASE( "Arithmetic Coding", "[coding]" ) {
  std::unique_ptr<arithzip::ArithmeticCompressor> compressor = std::make_unique<arithzip::ArithmeticCompressor>();
  std::unique_ptr<arithunzip::ArithmeticDecompressor> decompressor = std::make_unique<arithunzip::ArithmeticDecompressor>();
  const std::string in_message = "aaabbbbcc\n";

  // Read in the compressed model (was too long to store in this file
  std::string compressed_arithmetic_model_bin = "";
  std::ifstream model_fin{compressed_arithmetic_model_filename};
  char next_char;
  while (model_fin.get(next_char)) {
    compressed_arithmetic_model_bin += std::bitset<8>(next_char).to_string();
  }
  // Get rid of newline data
  compressed_arithmetic_model_bin = compressed_arithmetic_model_bin.substr(0, compressed_arithmetic_model_bin.length() - 8);
  const std::string model_bin = compressed_arithmetic_model_bin;
  const std::string compressed_data = "001000100101100001000010";
  const std::string byte_aligning_zeros = "";
  const std::string desired_bin = model_bin + compressed_data + byte_aligning_zeros;

  SECTION( "Arithmetic compression" ) {
    std::stringstream iss{in_message};
    std::stringstream oss;
    std::map<int, int> occurences;

    for (auto c : in_message) {
      ++occurences[c];
    }
    ++occurences[256];
    compressor->setModel(zip::Model{occurences});

    compressor->compressFile(iss, oss);
    char next_char;
    std::string actual_bin = "";
    while (oss.get(next_char)) {
      actual_bin += std::bitset<8>(next_char).to_string();
    }
    REQUIRE( actual_bin == desired_bin );
  }

  SECTION( "Arithmetic decompression" ) {
    std::stringstream iss;
    std::stringstream oss;
    zip::BitOut bout;
    bout.putBin(desired_bin, iss);

    decompressor->decompressFile(iss, oss);
    char next_char;
    std::string out_message = "";
    while (oss.get(next_char)) {
      out_message.push_back(next_char);
    }
    REQUIRE( in_message == out_message );
  }
}
