#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <memory>
#include <cstring>
#include "compressors/huffzip/huffman_compressor.h"
#include "compressors/arithzip/arithmetic_compressor.h"
#include "basic_display_service.h"
#include "model.h"

enum METHOD {
  HUFFMAN = 0,
  ARITHMETIC
};

int main(int argc, char** argv) {
  // Process arguments to determine following variables
  bool has_compression_method = false;
  METHOD m;
  std::string file_name = "";

  bool has_provided_file_name = false;
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "-m") ==  0 && !has_provided_file_name) {
      if (std::strcmp(argv[i + 1], "huffman") == 0) {
        m = HUFFMAN;
        has_compression_method = true;
      } else if (std::strcmp(argv[i + 1], "arithmetic") == 0) {
        m = ARITHMETIC;
        has_compression_method = true;
      } else {
        std::cerr << "ERROR: Invalid compression method \'" << argv[i + 1] << "\'" << std::endl;
        return 1;
      }
      ++i;
    } else {
      if (has_provided_file_name) {
        std::cerr << "ERROR: Multiple file compresson is not supported." << std::endl;
        return 2;
      }
      has_provided_file_name = true;
      file_name = argv[i];
    }
  }
  if (!has_compression_method) {
    std::cerr << "ERROR: Please specify a compression method using the -m option (see readme for current option values)" << std::endl;
    return 3;
  }

  std::unique_ptr<zip::DataCompressor> compressor = nullptr;
  if (m == HUFFMAN) {
    compressor = std::make_unique<huffzip::HuffmanCompressor>();
  } else {
    compressor = std::make_unique<arithzip::ArithmeticCompressor>();
  }
  std::unique_ptr<zip::DisplayService> display_service = std::make_unique<zip::BasicDisplayService>();
  display_service->setDisplayable(compressor.get());

  std::ifstream fin{file_name};

  // The pair of ull ull represents the fraction of the uncompressed data which
  // c is
  std::map<char, std::pair<unsigned long long, unsigned long long>> denominations;
  char c;
  unsigned long long count = 0;
  while (fin.get(c)) {
    ++count;
    ++denominations[c].first;
  }
  for (auto& p : denominations) p.second.second = count;
  compressor->setModel(zip::Model{denominations});
  compressor->compressFile(file_name);
  return 0;
}
