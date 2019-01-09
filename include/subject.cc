#include "subject.h"

void huffzip::Subject::notifyAllObservers() {
  for (auto& observer: observers) {
    observer->notify();
  }
}

void huffzip::Subject::addObserver(Observer* observer) {
  observers.push_back(observer);
}

void huffzip::Subject::removeObserver(Observer* observer) {
  auto it = observers.begin();
  for (it = observers.begin(); it != observers.end() && *it != observer; ++it);
  observers.erase(it);
}
