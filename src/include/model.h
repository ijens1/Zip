#ifndef MODEL_H
#define MODEL_H

#include <set>
#include <map>
#include <vector>

namespace zip {

  class Model {
      unsigned long long total_occurences = 0;
      std::map<int, std::pair<unsigned long long, unsigned long long>> ranges;
      std::set<std::pair<unsigned long long, int>> lower_bounds;
      std::vector<int> characters;

    public:
      Model() {}
      Model(std::map<int, unsigned long long>);
      Model(const Model&) = default;
      Model(Model&&) = default;
      Model& operator=(const Model&) = default;
      Model& operator=(Model&&) = default;
      ~Model() {}

      unsigned long long getTotalOccurences();
      std::pair<unsigned long long, unsigned long long> getRange(int);
      int getCharacter(unsigned long long);
      double getProb(int);
      const std::vector<int> getCharacters();
  };
}

#endif
