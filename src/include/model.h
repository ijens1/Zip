#ifndef MODEL_H
#define MODEL_H

#include <map>

namespace zip {

  struct Range {
    unsigned long long upper, lower, denominator;
  };

  // Model class to contain model behaviour and support possible adaptive modelling
  class Model {
      std::map<char, std::pair<unsigned long long, unsigned long long>> denominations;
      std::map<char, Range> ranges;

      void setRanges();

    public:
      Model() {}
      Model(std::map<char, std::pair<unsigned long long, unsigned long long>> initial_denominations) : denominations{initial_denominations} {
        setRanges();
      }
      Model(Model&) = default;
      Model(Model&&) = default;
      Model& operator=(Model&) = default;
      Model& operator=(Model&&) = default;
      ~Model() {}

      double getProb(char);
      Range getRange(char);

      std::map<char, std::pair<unsigned long long, unsigned long long>>::const_iterator begin() {
        return denominations.begin();
      }

      std::map<char, std::pair<unsigned long long, unsigned long long>>::const_iterator end() {
        return denominations.end();
      }
  };

}

#endif
