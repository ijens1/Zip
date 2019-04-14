#include <catch.hpp>
#include <sstream>
#include <bitset>
#include "bit_io.h"
#include "../../compressors/huffzip/huffman_compressor.h"
#include "../../decompressors/huffunzip/huffman_decompressor.h"

TEST_CASE( "Huffman Coding", "[coding]" ) {
  std::unique_ptr<huffzip::HuffmanCompressor> compressor = std::make_unique<huffzip::HuffmanCompressor>();
  std::unique_ptr<huffunzip::HuffmanDecompressor> decompressor = std::make_unique<huffunzip::HuffmanDecompressor>();
  const std::string in_message = "aaabbbbcc\n";
  const std::string file_length_bin = "00000000000000000000000000001010";
  const std::string model_bin = "010110001001011000010100001010101100011";
  const std::string compressed_data = "1010100000111111110";
  const std::string byte_aligning_zeros = "000000";
  const std::string desired_bin = file_length_bin + model_bin + compressed_data + byte_aligning_zeros;

  SECTION( "Huffman compression" ) {
    std::stringstream iss{in_message};
    std::stringstream oss;
    std::map<int, int> occurences;

    for (auto c : in_message) {
      ++occurences[c];
    }
    compressor->setModel(zip::Model{occurences});

    compressor->compressFile(iss, oss);
    char next_char;
    std::string actual_bin = "";
    while (oss.get(next_char)) {
      actual_bin += std::bitset<8>(next_char).to_string();
    }
    REQUIRE( actual_bin == desired_bin );
  }

  SECTION( "Huffman decompression" ) {
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
