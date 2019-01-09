#include "basic_compression_display_service.h"
#include "data_compressor.h"
#include <iostream>

void huffzip::BasicCompressionDisplayService::doSetCompressor(huffzip::ReadableDataCompressorInterface* compressor) {
  this->compressor = compressor;
  compressor->addObserver(this);
}

void huffzip::BasicCompressionDisplayService::doNotify() {
  std::string current_compressor_status = compressor->getCompressorState();
  std::cout << current_compressor_status << std::endl;
}
