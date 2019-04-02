#include "model.h"

zip::Model::Model(std::map<int, unsigned long long> occurences) {
  unsigned long long prev = 0;

  for (auto occurence : occurences) {
    lower_bounds.insert(std::make_pair(prev, occurence.first));
    ranges[occurence.first] = std::make_pair(prev, prev + occurence.second);
    characters.push_back(occurence.first);
    prev += occurence.second;
  }

  total_occurences = prev;
}

unsigned long long zip::Model::getTotalOccurences() {
  return total_occurences;
}

std::pair<unsigned long long, unsigned long long> zip::Model::getRange(int character) {
  return ranges[character];
}

int zip::Model::getCharacter(unsigned long long value) {
  auto it = lower_bounds.upper_bound(std::make_pair(value, 256));
  return (it == lower_bounds.end()) ? lower_bounds.rbegin()->second : it->second;
}

double zip::Model::getProb(int character) {
  auto range = ranges[character];
  return (double(range.second) - range.first) / total_occurences;
}

const std::vector<int> zip::Model::getCharacters() {
  return characters;
}
