#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include <iostream>
#include "subject.h"

namespace zip {

  class Displayable : public Subject {
      virtual std::string doGetState() const = 0;

    public:
      std::string getState() const { return doGetState(); }
  };

}

#endif
