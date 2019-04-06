#include <iostream>
#include <memory>
#include <cstring>
#include "decompressors/huffunzip/huffman_decompressor.h"
#include "decompressors/arithunzip/arithmetic_decompressor.h"
#include "basic_display_service.h"
#include "huffman_representation.h"
#include "arithmetic_representation.h"
#include "zip_exception.h"

enum METHOD {
  HUFFMAN = 0,
  ARITHMETIC
};

int main(int argc, char** argv) {
  // Process arguments to determine following variables
  bool has_decompression_method = false;
  METHOD m;
  std::string in_file_name = "";
  std::string out_file_name = "";

  bool has_provided_file_names = false;
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "-m") ==  0) {
      if (std::strcmp(argv[i + 1], "huffman") == 0) {
        m = HUFFMAN;
        has_decompression_method = true;
      } else if (std::strcmp(argv[i + 1], "arithmetic") == 0) {
        m = ARITHMETIC;
        has_decompression_method = true;
      } else {
        std::cerr << "ERROR: Invalid decompression method \'" << argv[i + 1] << "\'" << std::endl;
        return 1;
      }
      ++i;
    } else {
      if (has_provided_file_names) {
        std::cerr << "ERROR: Multiple file compresson is not supported." << std::endl;
        return 2;
      }
      has_provided_file_names = true;
      in_file_name = argv[i];
      out_file_name = argv[++i];
    }
  }
  if (!has_decompression_method) {
    std::cerr << "ERROR: Please specify a decompression method using the -m option (see readme for current option values)" << std::endl;
    return 3;
  }
  if (!has_provided_file_names) {
    std::cerr << "ERROR: Please specify a file to be compressed" << std::endl;
  }

  std::unique_ptr<zip::DataDecompressor> decompressor = nullptr;
  if (m == HUFFMAN) {
    decompressor = std::make_unique<huffunzip::HuffmanDecompressor>();
  } else if (m == ARITHMETIC) {
    decompressor = std::make_unique<arithunzip::ArithmeticDecompressor>();
  }

  std::unique_ptr<zip::DisplayService> display_service = std::make_unique<zip::BasicDisplayService>();
  display_service->setDisplayable(decompressor.get());

  try {
    decompressor->decompressFile(in_file_name, out_file_name);
  } catch (zip::ZipException& exc) {
    std::cerr << exc.getReason() << std::endl;
    return 3;
  }
  return 0;
}
