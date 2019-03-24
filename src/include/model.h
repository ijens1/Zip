#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <set>

namespace zip {

  struct CountComparator {
    bool operator() (const std::pair<unsigned long long, char>& lhs, const std::pair<unsigned long long, char>& rhs) {
      return lhs.first < rhs.first;
    }
  };

  struct Range {
    unsigned long long high, low, denominator;
  };

  // Model class to contain model behaviour and support possible adaptive modelling
  // Assumes that no character passed has an occurence value of zero
  // This assumption means that the search
  class Model {
      unsigned long long total_occurences;
      std::map<char, unsigned long long> occurences;
      std::map<char, Range> ranges;
      std::set<std::pair<unsigned long long, char>, CountComparator> search_set;
      void setRanges();

    public:
      Model() {}
      Model(std::map<char, unsigned long long> occurences) : occurences{occurences} {
        setRanges();
      }
      Model(Model&) = default;
      Model(Model&&) = default;
      Model& operator=(Model&) = default;
      Model& operator=(Model&&) = default;
      ~Model() {}

      double getProb(char);
      Range getRange(char);
      void incrementCharOccurence(char);
      size_t getNumElements();
      char getChar(unsigned long long);
      unsigned long long getTotalOccurences();

      std::map<char, unsigned long long>::const_iterator begin() {
        return occurences.begin();
      }

      std::map<char, unsigned long long>::const_iterator end() {
        return occurences.end();
      }
  };

}

#endif
