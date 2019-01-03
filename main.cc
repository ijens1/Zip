#include <fstream>
#include <map>
#include <algorithm>
#include "huffman_compressor.h"

int main() {
  std::unique_ptr<huffzip::HuffmanCompressor> compressor = std::make_unique<huffzip::HuffmanCompressor>();
  std::ifstream fin{"samplefile.txt"};
  std::map<char, double> pmf;
  char c;
  int count = 0;
  while (fin >> c) {
    ++count;
    ++pmf[c];
  }
  for (auto& freq : pmf) freq.second /= count;
  compressor->setProbabilityMassFunction(pmf);
  compressor->compressFile("samplefile.txt");
  return 0;
}
