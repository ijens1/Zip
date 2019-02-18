#ifndef MODEL_H
#define MODEL_H

#include <map>

namespace zip {

  struct Range {
    unsigned long long high, low, denominator;
  };

  // Model class to contain model behaviour and support possible adaptive modelling
  class Model {
      std::map<char, unsigned long long> occurences;
      std::map<char, Range> ranges;

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

      std::map<char, unsigned long long>::const_iterator begin() {
        return occurences.begin();
      }

      std::map<char, unsigned long long>::const_iterator end() {
        return occurences.end();
      }
  };

}

#endif
