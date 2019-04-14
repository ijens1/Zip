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

void huffunzip::HuffmanDecompressor::doDecompressFile(std::istream& sin, std::ostream& sout) {
  zip::BitIn fbin;

  decompressor_state = "Retrieving original file length...";
  notifyAllObservers();
  int uncompressed_file_length = retrieveUncompressedFileLength(sin);

  decompressor_state = "Retrieving encodings...";
  notifyAllObservers();

  std::vector<std::unique_ptr<zip::HuffmanNode>> nodes;
  zip::HuffmanNode *tree;

  generateEncodingTree(sin, nodes, fbin, tree);

  decompressor_state = "Decompressing file...";
  notifyAllObservers();
  int count = 0;
  while (count++ != uncompressed_file_length) sout.put(parseNextChar(sin, tree, fbin));
}

int huffunzip::HuffmanDecompressor::retrieveUncompressedFileLength(std::istream& in) {
  char c;
  int uncompressed_file_length = 0;
  for (int i = 0; i < 4; ++i) {
    int temp = 0;
    in.get(c);
    unsigned char c_u = c;
    temp |= c_u;
    uncompressed_file_length |= (temp << ((3 - i) * 8));
  }
  return uncompressed_file_length;
}

// Pre: std::istream& in must be position before encoded tree structure
void huffunzip::HuffmanDecompressor::generateEncodingTree(std::istream& sin, std::vector<std::unique_ptr<zip::HuffmanNode>>& nodes, zip::BitIn& fbin, zip::HuffmanNode*& curr_node) {
  unsigned char b;
  fbin.pullBit(b, sin);
  if (b == 1) {
    unsigned char c;
    fbin.pullByte(c, sin);
    nodes.push_back(std::make_unique<zip::HuffmanNode>(c, 0, nullptr, nullptr));
    curr_node = nodes.back().get();
  } else if (b == 0) {
    nodes.push_back(std::make_unique<zip::HuffmanNode>(0, 0, nullptr, nullptr));
    curr_node = nodes.back().get();
    generateEncodingTree(sin, nodes, fbin, curr_node->lchild);
    generateEncodingTree(sin, nodes, fbin, curr_node->rchild);
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
