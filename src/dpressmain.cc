#include <iostream>
#include <memory>
#include <cstring>
#include "decompressors/huffunzip/huffman_decompressor.h"
#include "decompressors/arithunzip/arithmetic_decompressor.h"
#include "basic_display_service.h"
#include "huffman_representation.h"
#include "arithmetic_representation.h"
#include "zip_exception.h"

int main(int argc, char** argv) {
  if (argc > 3) {
    std::cerr << "ERROR: Please provide a single compressed file to decompress" << std::endl;
    return 1;
  }

  // Determine the type of compressed data we're dealing with. Probably best to
  // deal with the magic number instead of the file name.
  std::ifstream fin{argv[1]};

  //std::string magic_number_str = "";
  //char c;
  //for (size_t i = 0; i < zip::huffman_magic_number_str.length(); ++i) {
    //fin.get(c);
    //magic_number_str += c;
  //}

  std::unique_ptr<zip::DataDecompressor> decompressor = nullptr;
  //if (magic_number_str == zip::huffman_magic_number_str) {
    //decompressor = std::make_unique<huffunzip::HuffmanDecompressor>();
  //} else if (magic_number_str == zip::arithmetic_magic_number_str) {
    decompressor = std::make_unique<arithunzip::ArithmeticDecompressor>();
  //} else {
    //std::cerr << "ERROR: Unable to determine compression format for file\nAborting..." << std::endl;
    //return 2;
  //}

  std::unique_ptr<zip::DisplayService> display_service = std::make_unique<zip::BasicDisplayService>();
  display_service->setDisplayable(decompressor.get());

  try {
    decompressor->decompressFile(argv[1], argv[2]);
  } catch (zip::ZipException& exc) {
    std::cerr << exc.getReason() << std::endl;
    return 3;
  }
  return 0;
}
