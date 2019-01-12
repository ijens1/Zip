#ifndef DISPLAY_SERVICE_H
#define DISPLAY_SERVICE_H

#include "observer.h"

namespace zip {

  class Displayable;

  class DisplayService : public Observer {
      virtual void doSetDisplayable(Displayable*) = 0;
      virtual void doNotify() = 0;

    public:
      void notify() override { doNotify(); }
      void setDisplayable(Displayable* displayable) { doSetDisplayable(displayable); }
  };

}


#endif
