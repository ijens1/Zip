#include "huffman_compressor.h"
#include <iostream>

std::string huffzip::HuffmanCompressor::doGetCompressorState() const {
  return compression_state;
}

double huffzip::HuffmanCompressor::doGetPercentComplete() const {
  return 0;
}

void huffzip::HuffmanCompressor::doSetProbabilityMassFunction(std::map<char, double> pmf) {
  this->pmf = pmf;
}

void huffzip::HuffmanCompressor::doCompressFile(std::string file_name) {
  std::string file_core = file_name.substr(0, file_name.find('.') + 1);

  // Construct the nodes
  std::vector<std::unique_ptr<HuffmanNode>> nodes;
  for (auto& i : pmf) {
    nodes.push_back(std::make_unique<HuffmanNode>(i.first, i.second, nullptr, nullptr));
  }

  // Insert the nodes into the priority queue and construct the tree
  std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareHuffmanNode> pq;
  for (auto& node : nodes) pq.push(node.get());

  while (pq.size() != 1) {
    HuffmanNode* n1 = pq.top();
    pq.pop();
    HuffmanNode* n2 = pq.top();
    pq.pop();
    nodes.push_back(std::make_unique<HuffmanNode>(n1->c + n2->c, n1->prob + n2->prob, n1, n2));
    pq.push(nodes.back().get());
  }

  // Determine the encodings
  std::map<char, std::string> encodings;
  determineEncodings(encodings, pq.top(), "");

  for (auto& encoding : encodings) {
    std::cout << encoding.first << " mapped to " << encoding.second << std::endl;
  }
}

void huffzip::HuffmanCompressor::determineEncodings(std::map<char, std::string>& encodings, HuffmanNode* curr_node, std::string curr_encoding) {
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

