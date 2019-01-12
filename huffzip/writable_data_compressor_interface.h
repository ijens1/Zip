#ifndef WRITABLE_DATA_COMPRESSION_INTERFACE_H
#define WRITABLE_DATA_COMPRESSION_INTERFACE_H

#include <map>

namespace huffzip {

  class WritableDataCompressorInterface {
      virtual void doSetProbabilityMassFunction(std::map<char, double>) = 0;

    public:
      virtual ~WritableDataCompressorInterface() = default;
      void setProbabilityMassFunction(std::map<char, double> pmf) { doSetProbabilityMassFunction(pmf); }
  };

}

#endif
