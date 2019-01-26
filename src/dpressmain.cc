#include <iostream>
#include <memory>
#include <cstring>
#include "decompressors/huffunzip/huffman_decompressor.h"
#include "decompressors/arithunzip/arithmetic_decompressor.h"
#include "basic_display_service.h"
#include "zip_exception.h"

int main(int argc, char** argv) {
  if (argc > 2) {
    std::cerr << "Program does not support multiple file decompression at the moment" << std::endl;
    return 1;
  }
  if (!std::strcmp(argv[1], "huffman") && !std::strcmp(argv[1], "arithmetic")) {
    std::cerr << "Invalid decompression form. Second argument must be one of \'huffman\' or \'arithmetic\'" << std::endl;
    return 2;
  }
  std::unique_ptr<zip::DataDecompressor> decompressor = nullptr;
  if (std::strcmp(argv[1], "huffman")) {
    decompressor = std::make_unique<huffunzip::HuffmanDecompressor>();
  } else {
    decompressor = std::make_unique<arithunzip::ArithmeticDecompressor>();
  }
  std::unique_ptr<zip::DisplayService> display_service = std::make_unique<zip::BasicDisplayService>();
  display_service->setDisplayable(decompressor.get());

  try {
    decompressor->decompressFile(argv[2]);
  } catch (zip::ZipException& exc) {
    std::cerr << exc.getReason() << std::endl;
    return 2;
  }
  return 0;
}
