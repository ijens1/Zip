#ifndef DATA_DECOMPRESSOR_H
#define DATA_DECOMPRESSOR_H

#include "readable_data_decompressor_interface.h"
#include <string>
#include <istream>
#include <ostream>

namespace zip {

  class DataDecompressor : public ReadableDataDecompressorInterface {
      virtual void doDecompressFile(std::istream&, std::ostream&) = 0;

    public:
      void decompressFile(std::istream& istream, std::ostream& ostream) { doDecompressFile(istream, ostream); }
  };

}

#endif
