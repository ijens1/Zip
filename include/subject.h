#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

namespace huffzip {

  class Subject {
      std::vector<Observer*> observers;

    public:
      virtual ~Subject() = default;

      void notifyAllObservers();
      void addObserver(Observer*);
      void removeObserver(Observer*);
  };
}
#endif
