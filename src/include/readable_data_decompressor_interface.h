#ifndef READABLE_DATA_DECOMPRESSOR_INTERFACE_H
#define READABLE_DATA_DECOMPRESSOR_INTERFACE_H

#include "displayable.h"

namespace zip {

  class ReadableDataDecompressorInterface : public zip::Displayable {
      virtual double doGetPercentComplete() const = 0;

    public:
      double getPercentComplete() { return doGetPercentComplete(); }

  };

}

#endif
