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
  // Decompress to current dir
  if (file_core.find('/') != std::string::npos) file_core = file_core.substr(file_core.rfind('/') + 1);

  std::ifstream fin{file_name, std::ios::binary | std::ios::in};
  zip::BitIn fbin;

  decompressor_state = "Checking magic number...";
  notifyAllObservers();

  char c;
  std::string magic_number_str;
  for (int i = 0; i < 4; ++i) {
    fin.get(c);
    magic_number_str += c;
  }
  if (magic_number_str != zip::magic_number_str) {
    throw zip::ZipException{"The provided .hz file is corrupted\nTerminating..."};
  }

  decompressor_state = "Retrieving original file length...";
  notifyAllObservers();
  unsigned long long uncompressed_file_length = retrieveUncompressedFileLength(fin);

  unsigned char original_file_extension_length = 0;

  decompressor_state = "Retrieving original file extension...";
  notifyAllObservers();
  fin >> original_file_extension_length;

  std::string original_file_extension;

  for (int i = 0; i < original_file_extension_length; ++i) {
    fin.get(c);
    original_file_extension += c;
  }

  decompressor_state = "Retrieving encodings...";
  notifyAllObservers();

  std::vector<std::unique_ptr<zip::HuffmanNode>> nodes;
  zip::HuffmanNode *tree;

  generateEncodingTree(fin, nodes, fbin, tree);

  // Now we have all the information we need to generate the original file.
  std::ofstream fout{file_core + "." + original_file_extension};

  decompressor_state = "Decompressing file...";
  notifyAllObservers();
  unsigned long long count = 0;
  while (count++ != uncompressed_file_length) fout << parseNextChar(fin, tree, fbin);
}

unsigned long long huffunzip::HuffmanDecompressor::retrieveUncompressedFileLength(std::istream& in) {
  char c;
  unsigned long long ufl = 0;
  for (int i = 0; i < 8; ++i) {
    unsigned long long temp = 0;
    in.get(c);
    unsigned char c_u = c;
    temp |= c_u;
    ufl |= (temp << ((7 - i) * 8));
  }
  return ufl;
}

// Pre: std::istream& in must be position before encoded tree structure
void huffunzip::HuffmanDecompressor::generateEncodingTree(std::istream& in, std::vector<std::unique_ptr<zip::HuffmanNode>>& nodes, zip::BitIn& fbin, zip::HuffmanNode*& curr_node) {
  unsigned char b;
  fbin.pullBit(b, in);
  if (b == 1) {
    unsigned char c;
    fbin.pullByte(c, in);
    nodes.push_back(std::make_unique<zip::HuffmanNode>(c, 0, nullptr, nullptr));
    curr_node = nodes.back().get();
  } else if (b == 0) {
    nodes.push_back(std::make_unique<zip::HuffmanNode>(0, 0, nullptr, nullptr));
    curr_node = nodes.back().get();
    generateEncodingTree(in, nodes, fbin, curr_node->lchild);
    generateEncodingTree(in, nodes, fbin, curr_node->rchild);
  }
}


char huffunzip::HuffmanDecompressor::parseNextChar(std::istream& in, zip::HuffmanNode *tree, zip::BitIn& fbin) {
  while (!(tree->lchild == nullptr && tree->rchild == nullptr)) {
    unsigned char b;
    fbin.pullBit(b, in);
    if (b == 0) {
      tree = tree->lchild;
    } else if (b == 1) {
      tree = tree->rchild;
    }
  }
  return tree->c;
}
