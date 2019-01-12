#include "basic_display_service.h"
#include "displayable.h"
#include <iostream>

void zip::BasicDisplayService::doSetDisplayable(zip::Displayable* displayable) {
  this->displayable = displayable;
  displayable->addObserver(this);
}

void zip::BasicDisplayService::doNotify() {
  std::string current_displayable_state = displayable->getState();
  std::cout << current_displayable_state << std::endl;
}
