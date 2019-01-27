#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <memory>
#include <cstring>
#include "compressors/huffzip/huffman_compressor.h"
#include "compressors/arithzip/arithmetic_compressor.h"
#include "basic_display_service.h"

int main(int argc, char** argv) {
  if (argc > 3) {
    std::cerr << "Program does not support multiple file compression at the moment" << std::endl;
    return 1;
  }
  if (std::strcmp(argv[1], "huffman") != 0 && std::strcmp(argv[1], "arithmetic") != 0) {
    std::cerr << "Invalid compression form. Second argument must be one of \'huffman\' or \'arithmetic\'" << std::endl;
    return 2;
  }
  std::unique_ptr<zip::DataCompressor> compressor = nullptr;
  if (std::strcmp(argv[1], "huffman") == 0) {
    compressor = std::make_unique<huffzip::HuffmanCompressor>();
  } else {
    compressor = std::make_unique<arithzip::ArithmeticCompressor>();
  }
  std::unique_ptr<zip::DisplayService> display_service = std::make_unique<zip::BasicDisplayService>();
  display_service->setDisplayable(compressor.get());

  std::ifstream fin{argv[2]};
  std::map<char, double> pmf;
  char c;
  int count = 0;
  while (fin.get(c) && c != '\n') {
    ++count;
    ++pmf[c];
  }
  for (auto& freq : pmf) freq.second /= count;
  compressor->setProbabilityMassFunction(pmf);
  compressor->compressFile(argv[2]);
  return 0;
}
