#ifndef OBSERVER_H
#define OBSERVER_H

namespace huffzip {

  class Observer {
    public:
      virtual ~Observer() = default;
      virtual void notify() = 0;
  };

}

#endif
