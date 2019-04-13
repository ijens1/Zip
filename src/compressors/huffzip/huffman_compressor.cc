#include <fstream>
#include <bitset>
#include <algorithm>
#include "huffman_compressor.h"
#include "huffman_representation.h"
#include "bit_io.h"
#include "zip_exception.h"

std::string huffzip::HuffmanCompressor::doGetState() const {
  return compressor_state;
}

double huffzip::HuffmanCompressor::doGetPercentComplete() const {
  return 0;
}

void huffzip::HuffmanCompressor::doSetModel(zip::Model model) {
  this->model = model;
}

void huffzip::HuffmanCompressor::doCompressFile(std::istream& sin, std::ostream& sout) {
  compressor_state = "Generating encodings...";
  notifyAllObservers();

  std::vector<std::unique_ptr<zip::HuffmanNode>> nodes;
  for (auto character : model.getCharacters()) {
    // Don't use EOF character for this compression method
    if (character != 256) {
      nodes.push_back(std::make_unique<zip::HuffmanNode>(character, model.getProb(character), nullptr, nullptr));
    }
  }

  // Insert the nodes into the priority queue and construct the tree
  // Note that even though there is a call to new here, they should all be
  // eventually assigned to a smart pointer
  std::priority_queue<zip::HuffmanNode*, std::vector<zip::HuffmanNode*>, zip::CompareHuffmanNode> pq;
  for (auto& node : nodes) pq.push(node.get());

  while (pq.size() != 1) {
    zip::HuffmanNode* n1 = pq.top();
    pq.pop();
    zip::HuffmanNode* n2 = pq.top();
    pq.pop();

    // Make sure to keep RAII on all nodes created
    nodes.push_back(std::make_unique<zip::HuffmanNode>(n1->c + n2->c, n1->prob + n2->prob, n1, n2));
    pq.push(nodes.back().get());
  }

  // Determine the encodings
  zip::HuffmanNode* tree = pq.top();
  pq.pop();
  std::map<char, std::string> encodings;
  determineEncodings(encodings, tree, "");

  // Declare bit output object
  zip::BitOut fbout;

  std::string uncompressed_data;
  std::string line;
  // File size in bytes
  unsigned long long file_size = 0;
  while (std::getline(sin, line)) {
    uncompressed_data += line + '\n';
    file_size += line.size() + 1;
  }

  // Generate compressed tree for decompression
  std::string compressed_data;
  generateCompressedTree(tree, compressed_data);

  compressor_state = "Writing uncompressed data size...";
  notifyAllObservers();

  sout << char(file_size >> 56) << char(file_size >> 48) << char(file_size >> 40) << char(file_size >> 32) << char(file_size >> 24) << char(file_size >> 16) << char(file_size >> 8) << char(file_size);

  compressor_state = "Writing compression model and compressed data...";
  notifyAllObservers();

  // Compress data
  for (auto c : uncompressed_data) {
    compressed_data += encodings[c];
  }
  fbout.putBin(compressed_data, sout);
}

void huffzip::HuffmanCompressor::determineEncodings(std::map<char, std::string>& encodings, const zip::HuffmanNode* const curr_node, std::string curr_encoding) const {
  if (curr_node->lchild == nullptr && curr_node->rchild == nullptr) {
    encodings[curr_node->c] = curr_encoding;
  } else {
    if (curr_node->lchild != nullptr) {
      determineEncodings(encodings, curr_node->lchild, curr_encoding + "0");
    }
    if (curr_node->rchild != nullptr) {
      determineEncodings(encodings, curr_node->rchild, curr_encoding + "1");
    }
  }
}

// Encode leaf node as 1. When decompressing, when you read in a one, just read
// in the next byte to find out what the char is for that leaf.
void huffzip::HuffmanCompressor::generateCompressedTree(const zip::HuffmanNode *const tree, std::string& compressed_tree) const {
  if (tree->lchild == nullptr && tree->rchild == nullptr) {
    compressed_tree += '1' + std::bitset<8>(tree->c).to_string();

    // We know both children must be non-nullptr
  } else {
    compressed_tree += '0';
    generateCompressedTree(tree->lchild, compressed_tree);
    generateCompressedTree(tree->rchild, compressed_tree);
  }
}
