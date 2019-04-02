#ifndef DATA_DECOMPRESSOR_H
#define DATA_DECOMPRESSOR_H

#include "readable_data_decompressor_interface.h"
#include <string>

namespace zip {

  class DataDecompressor : public ReadableDataDecompressorInterface {
      virtual void doDecompressFile(std::string, std::string) = 0;

    public:
      void decompressFile(std::string in_file_name, std::string out_file_name) { doDecompressFile(in_file_name, out_file_name); }
  };

}

#endif
