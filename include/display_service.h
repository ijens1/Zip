#ifndef DISPLAY_SERVICE_H
#define DISPLAY_SERVICE_H

#include "observer.h"

namespace huffzip {

  class Displayable;

  class DisplayService : public Observer {
      virtual void doSetDisplayable(huffzip::Displayable*) = 0;
      virtual void doNotify() = 0;

    public:
      void notify() override { doNotify(); }
      void setDisplayable(huffzip::Displayable* displayable) { doSetDisplayable(displayable); }
  };

}


#endif
