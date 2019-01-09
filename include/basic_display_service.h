#ifndef BASIC_COMPRESSION_DISPLAY_SERVICE
#define BASIC_COMPRESSION_DISPLAY_SERVICE

#include "display_service.h"

namespace huffzip {

  class BasicCompressionDisplayService : public CompressionDisplayService {
      huffzip::ReadableDataCompressorInterface* compressor;

      void doSetCompressor(huffzip::ReadableDataCompressorInterface*) override;
      void doNotify() override;
  };
}


#endif
