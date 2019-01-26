#ifndef DATA_DECOMPRESSOR_H
#define DATA_DECOMPRESSOR_H

#include "readable_data_decompressor_interface.h"
#include <string>

namespace zip {

  class DataDecompressor : public ReadableDataDecompressorInterface {
      virtual void doDecompressFile(std::string) = 0;

    public:
      void decompressFile(std::string file_name) { doDecompressFile(file_name); }
  };

}

#endif
