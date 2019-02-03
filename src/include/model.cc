#include "model.h"
#include "zip_exception.h"

void zip::Model::setRanges() {
  // Construct the alphabetically sorted ranges
  unsigned long long curr_min = 0;

  for (auto& p : denominations) {
    ranges[p.first] = Range{curr_min + p.second.first, curr_min, p.second.second};
    curr_min += p.second.first;
  }
}

double zip::Model::getProb(char c) {
  if (denominations.count(c) != 1) {
    std::string what = "ERROR: No probability value found for character \'";
    what.push_back(c);
    what += "\'";
    throw zip::ZipException{what};
  }
  std::pair<unsigned long long, unsigned long long> frac = denominations.at(c);
  return frac.first / frac.second;
}

zip::Range zip::Model::getRange(char c) {
  if (denominations.count(c) != 1) {
    std::string what = "ERROR: No probability value found for character \'";
    what.push_back(c);
    what += "\'";
    throw zip::ZipException{what};
  }
  return ranges.at(c);
}
