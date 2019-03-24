#include <iostream>
#include "model.h"
#include "zip_exception.h"

void zip::Model::setRanges() {
  // Construct the alphabetically sorted ranges
  unsigned long long curr_min = 0;
  unsigned long long count = 0;

  for (auto& o : occurences) {
    count += o.second;
    ranges[o.first] = Range{curr_min + o.second, curr_min, 0};
    search_set.insert(std::make_pair(curr_min, o.first));
    curr_min += o.second;
  }

  for (auto& r : ranges) {
    r.second.denominator = count;
  }

  total_occurences = count;
}

double zip::Model::getProb(char c) {
  if (occurences.count(c) != 1) {
    std::string what = "ERROR: No probability value found for character \'";
    what.push_back(c);
    what += "\'";
    throw zip::ZipException{what};
  }
  Range r = ranges.at(c);
  return (r.high - r.low) / r.denominator;
}

zip::Range zip::Model::getRange(char c) {
  if (occurences.count(c) != 1) {
    std::string what = "ERROR: No probability value found for character \'";
    what.push_back(c);
    what += "\'";
    throw zip::ZipException{what};
  }
  return ranges.at(c);
}

void zip::Model::incrementCharOccurence(char c) {
  ++occurences[c];

  // Shouldn't be too inefficient since we are only iterating over the length
  // of the alphabet
  setRanges();
}

size_t zip::Model::getNumElements() {
  return occurences.size();
}

// Count isn't the actual count of the character. It includes all the
// counts of the characters that alphabetically come before it.
char zip::Model::getChar(unsigned long long count) {
  // This line should never resolve based on character value since each
  // character in the search set has non-zero occurence count
  std::set<std::pair<unsigned long long, char>>::iterator i = search_set.upper_bound(std::make_pair(count, 255));
  return (i == search_set.end()) ? search_set.rbegin()->second : (--i)->second;
}

unsigned long long zip::Model::getTotalOccurences() {
  return total_occurences;
}
