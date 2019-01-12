#include <iostream>
#include <fstream>
#include "huffman_decompressor.h"
#include "huffman_representation.h"
#include "zip_exception.h"

std::string huffunzip::HuffmanDecompressor::doGetState() const {
  return decompressor_state;
}

double huffunzip::HuffmanDecompressor::doGetPercentComplete() const {
  return 0.0;
}

void huffunzip::HuffmanDecompressor::doDecompressFile(std::string file_name) {
  std::string file_extension = file_name.substr(file_name.find('.'));

  if (file_extension != zip::huffman_file_extension) {
    throw zip::ZipException{"Cannot decompress " + file_extension + " file with huffman decompression\nTerminating..."};
  }

  std::ifstream fin{file_name};

  char c;
  std::string magic_number_str;
  for (int i = 0; i < 4; ++i) {
    fin >> c;
    magic_number_str += c;
  }
  if (magic_number_str != zip::magic_number_str) {
    throw zip::ZipException{"The provided .hz file is corrupted\nTerminating..."};
  }

  unsigned long long int uncompressed_file_size = 0;
  fin >> uncompressed_file_size;

  std::cout << uncompressed_file_size << std::endl;

}
