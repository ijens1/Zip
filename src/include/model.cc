#include "model.h"
#include "zip_exception.h"

void zip::Model::setRanges() {
  // Construct the alphabetically sorted ranges
  unsigned long long curr_min = 0;
  unsigned long long count = 0;

  for (auto& o : occurences) {
    count += o.second;
    ranges[o.first] = Range{curr_min + o.second, curr_min, 0};
    curr_min += o.second;
  }

  for (auto& r : ranges) {
    r.second.denominator = count;
  }
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
