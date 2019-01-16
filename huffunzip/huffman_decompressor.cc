#include <iostream>
#include <fstream>
#include <bitset>
#include <stack>
#include "huffman_decompressor.h"
#include "huffman_representation.h"
#include "zip_exception.h"
#include "bit_io.h"

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

  std::string file_core = file_name.substr(0, file_name.find('.'));

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

  unsigned long long uncompressed_file_length = retrieveUncompressedFileLength(fin);

  std::cout << uncompressed_file_length << std::endl;

  unsigned char original_file_extension_length = 0;

  fin >> original_file_extension_length;

  std::string original_file_extension;

  for (int i = 0; i < original_file_extension_length; ++i) {
    fin >> c;
    original_file_extension += c;
  }

  std::cout << original_file_extension << std::endl;

  std::unique_ptr<zip::HuffmanNode> encoding_tree = generateEncodingTree(fin);
}

unsigned long long huffunzip::HuffmanDecompressor::retrieveUncompressedFileLength(std::istream& in) {
  unsigned char c;
  unsigned long long ufl = 0;
  for (int i = 0; i < 8; ++i) {
    unsigned long long temp = 0;
    in >> c;
    temp |= c;
    ufl |= (temp << ((7 - i) * 8));
  }
  return ufl;
}

// Pre: std::istream& in must be position before encoded tree structure
std::unique_ptr<zip::HuffmanNode> huffunzip::HuffmanDecompressor::generateEncodingTree(std::istream& in) {
  zip::BitIn fbin;
  std::stack<std::unique_ptr<zip::HuffmanNode>> node_s;
  while (true) {
    char b;
    fbin.pullBit(b, in);
  }
}

