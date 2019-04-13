#ifndef BASIC_DISPLAY_SERVICE
#define BASIC_DISPLAY_SERVICE

#include "display_service.h"
#include <ostream>

namespace zip {

  class BasicDisplayService : public DisplayService {
      zip::Displayable* displayable;
      std::ostream& os;

      void doSetDisplayable(zip::Displayable*) override;
      void doNotify() override;
    public:
      BasicDisplayService(std::ostream& os) : os{os} {}
  };

}


#endif
