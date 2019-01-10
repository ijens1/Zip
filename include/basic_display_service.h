#ifndef BASIC_DISPLAY_SERVICE
#define BASIC_DISPLAY_SERVICE

#include "display_service.h"

namespace huffzip {

  class BasicDisplayService : public DisplayService {
      huffzip::Displayable* displayable;

      void doSetDisplayable(huffzip::Displayable*) override;
      void doNotify() override;
  };
}


#endif
