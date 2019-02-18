#include "arithmetic_decompressor.h"
#include "arithmetic_representation.h"
#include "bit_io.h"
#include "zip_exception.h"

std::string arithunzip::ArithmeticDecompressor::doGetState() const {
  return decompressor_state;
}

double arithunzip::ArithmeticDecompressor::doGetPercentComplete() const {
  return 0;
}

void arithunzip::ArithmeticDecompressor::doDecompressFile(std::string file_name) {
  std::string file_extension = file_name.substr(file_name.find('.'));

  std::string file_core = file_name.substr(0, file_name.find('.'));
  // Decompress to current dir
  if (file_core.find('/') != std::string::npos) file_core = file_core.substr(file_core.rfind('/') + 1);

  std::ifstream fin{file_name, std::ios::binary | std::ios::in};
  zip::BitIn fbin;

  decompressor_state = "Checking magic number...";
  notifyAllObservers();

  char c;
  std::string magic_number_str;
  for (size_t i = 0; i < zip::arithmetic_magic_number_str.length(); ++i) {
    fin.get(c);
    magic_number_str += c;
  }
  if (magic_number_str != zip::arithmetic_magic_number_str) {
    throw zip::ZipException{"ERROR: The provided .az file is corrupted\nTerminating..."};
  }

  unsigned char original_file_extension_length = 0;

  decompressor_state = "Retrieving original file extension...";
  notifyAllObservers();
  fin >> original_file_extension_length;

  std::string original_file_extension;

  for (int i = 0; i < original_file_extension_length; ++i) {
    fin.get(c);
    original_file_extension += c;
  }

  std::cout << original_file_extension << std::endl;

}
