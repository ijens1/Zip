#ifndef DATA_COMPRESSOR_H
#define DATA_COMPRESSOR_H

#include "readable_data_compressor_interface.h"
#include "writable_data_compressor_interface.h"

namespace zip {

  class DataCompressor: public ReadableDataCompressorInterface, public WritableDataCompressorInterface {
      virtual void doCompressFile(std::string, std::string) = 0;

    public:
      virtual ~DataCompressor() = default;
      void compressFile(std::string in_file_name, std::string out_file_name) { doCompressFile(in_file_name, out_file_name); }
  };
}

#endif
