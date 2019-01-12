#include "subject.h"

void zip::Subject::notifyAllObservers() {
  for (auto& observer: observers) {
    observer->notify();
  }
}

void zip::Subject::addObserver(Observer* observer) {
  observers.push_back(observer);
}

void zip::Subject::removeObserver(Observer* observer) {
  auto it = observers.begin();
  for (it = observers.begin(); it != observers.end() && *it != observer; ++it);
  observers.erase(it);
}
