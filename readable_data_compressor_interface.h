#ifndef READABLE_DATA_COMPRESSION_INTERFACE_H
#define READABLE_DATA_COMPRESSION_INTERFACE_H

#include "subject.h"

namespace huffzip {

  class ReadableDataCompressorInterface : public Subject {
      virtual std::string doGetCompressorState() const = 0;
      virtual double doGetPercentComplete() const = 0;

    public:
      virtual ~ReadableDataCompressorInterface() = default;

      std::string getCompressorState() const { return doGetCompressorState(); }
      double getPercentageComplete() const { return doGetPercentComplete(); }
  };
}

#endif
