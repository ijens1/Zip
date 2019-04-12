#include <catch.hpp>
#include <sstream>
#include <string>
#include "bit_io.h"

TEST_CASE( "BitIn accurately pulls data", "[include]" ) {

  zip::BitIn bin;
  const std::string in_message = "Hello World!";
  std::stringstream iss(in_message);

  SECTION( "pulling bit by bit is correct" ) {
    unsigned char next_char;
    std::string final_bin_str = "";
    for (unsigned int i = 0; i < in_message.length() * 8; ++i) {
      bin.pullBit(next_char, iss);
      final_bin_str.push_back(char(next_char + 48));
    }
    REQUIRE( final_bin_str == "010010000110010101101100011011000110111100100000010101110110111101110010011011000110010000100001" );
  }

  SECTION( "pulling byte by byte is correct") {
    unsigned char next_byte;
    std::string final_str = "";
    for (unsigned int i = 0; i < in_message.length(); ++i) {
      bin.pullByte(next_byte, iss);
      final_str.push_back(char(next_byte));
    }
    REQUIRE( final_str == in_message );
  }
}

TEST_CASE( "BitOut accurately outputs data", "[include]" ) {

  zip::BitOut bout;
  const std::string out_message = "010010000110010101101100011011000110111100100000010101110110111101110010011011000110010000100001";
  std::stringstream oss;

  SECTION( "ouputting byte aligned data adds no extra data" ) {
    bout.putBin(out_message, oss);
    std::string message;
    std::getline(oss, message);
    REQUIRE( message.length() == out_message.length() / 8);
  }
}
