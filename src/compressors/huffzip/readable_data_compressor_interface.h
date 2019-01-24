#ifndef READABLE_DATA_COMPRESSION_INTERFACE_H
#define READABLE_DATA_COMPRESSION_INTERFACE_H

#include <string>
#include "displayable.h"

namespace huffzip {

  class ReadableDataCompressorInterface : public zip::Displayable {
      virtual double doGetPercentComplete() const = 0;

    public:
      virtual ~ReadableDataCompressorInterface() = default;

      double getPercentageComplete() const { return doGetPercentComplete(); }
  };
}

#endif
