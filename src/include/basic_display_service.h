#ifndef BASIC_DISPLAY_SERVICE
#define BASIC_DISPLAY_SERVICE

#include "display_service.h"

namespace zip {

  class BasicDisplayService : public DisplayService {
      zip::Displayable* displayable;

      void doSetDisplayable(zip::Displayable*) override;
      void doNotify() override;
  };

}


#endif
