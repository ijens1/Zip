#ifndef WRITABLE_DATA_COMPRESSION_INTERFACE_H
#define WRITABLE_DATA_COMPRESSION_INTERFACE_H

#include <map>
#include "model.h"

namespace zip {

  class WritableDataCompressorInterface {
      virtual void doSetModel(Model model) = 0;

    public:
      virtual ~WritableDataCompressorInterface() = default;
      void setModel(Model model) { doSetModel(model); }
  };

}

#endif
