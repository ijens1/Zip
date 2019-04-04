#ifndef MODEL_H
#define MODEL_H

#include <set>
#include <map>
#include <vector>

namespace zip {

  class Model {
      int total_occurences = 0;
      std::map<int, std::pair<int, int>> ranges;
      std::set<std::pair<int, int>> lower_bounds;
      std::vector<int> characters;

    public:
      Model() {}
      Model(std::map<int, int>);
      Model(const Model&) = default;
      Model(Model&&) = default;
      Model& operator=(const Model&) = default;
      Model& operator=(Model&&) = default;
      ~Model() {}

      int getTotalOccurences();
      std::pair<int, int> getRange(int);
      int getCharacter(int);
      double getProb(int);
      const std::vector<int> getCharacters();
  };
}

#endif
