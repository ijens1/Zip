#include <iostream>
#include <memory>
#include "decompressors/arithunzip/arithmetic_decompressor.h"
#include "basic_display_service.h"
#include "zip_exception.h"

int main(int argc, char** argv) {
  if (argc > 2) {
    std::cerr << "Program does not support multiple file decompression at the moment" << std::endl;
    return 1;
  }
  std::unique_ptr<huffunzip::DataDecompressor> decompressor = std::make_unique<arithunzip::ArithmeticDecompressor>();
  std::unique_ptr<zip::DisplayService> display_service = std::make_unique<zip::BasicDisplayService>();
  display_service->setDisplayable(decompressor.get());

  try {
    decompressor->decompressFile(argv[1]);
  } catch (zip::ZipException& exc) {
    std::cerr << exc.getReason() << std::endl;
    return 2;
  }
  return 0;
}
