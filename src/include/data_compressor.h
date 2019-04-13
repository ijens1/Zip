#ifndef DATA_COMPRESSOR_H
#define DATA_COMPRESSOR_H

#include "readable_data_compressor_interface.h"
#include "writable_data_compressor_interface.h"
#include <istream>
#include <ostream>

namespace zip {

  class DataCompressor: public ReadableDataCompressorInterface, public WritableDataCompressorInterface {
      virtual void doCompressFile(std::istream&, std::ostream&) = 0;

    public:
      virtual ~DataCompressor() = default;
      void compressFile(std::istream& istream, std::ostream& ostream) { doCompressFile(istream, ostream); }
  };
}

#endif
