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
    throw zip::ZipException{"Cannot decompress " + file_extension + " file with huffman decompression"};
  }
}
