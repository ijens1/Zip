#ifndef DATA_COMPRESSOR_H
#define DATA_COMPRESSOR_H

#include "readable_data_compressor_interface.h"
#include "writable_data_compressor_interface.h"

namespace huffzip {

  class DataCompressor: public ReadableDataCompressorInterface, public WritableDataCompressorInterface {
      virtual void doCompressFile(std::string) = 0;

    public:
      virtual ~DataCompressor() = default;
      void compressFile(std::string fileName) { doCompressFile(fileName); }
  };
}

#endif
