#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <memory>
#include "compressors/arithzip/arithmetic_compressor.h"
#include "basic_display_service.h"

int main(int argc, char** argv) {
  if (argc > 2) {
    std::cerr << "Program does not support multiple file compression at the moment" << std::endl;
    return 1;
  }
  std::unique_ptr<huffzip::DataCompressor> compressor = std::make_unique<arithzip::ArithmeticCompressor>();
  std::unique_ptr<zip::DisplayService> display_service = std::make_unique<zip::BasicDisplayService>();
  display_service->setDisplayable(compressor.get());

  std::ifstream fin{argv[1]};
  std::map<char, double> pmf;
  char c;
  int count = 0;
  while (fin.get(c)) {
    ++count;
    ++pmf[c];
  }
  for (auto& freq : pmf) freq.second /= count;
  compressor->setProbabilityMassFunction(pmf);
  compressor->compressFile(argv[1]);
  return 0;
}
