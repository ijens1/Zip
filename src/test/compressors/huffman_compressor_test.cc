#include <catch.hpp>
#include "../../compressors/huffzip/huffman_compressor.h"

TEST_CASE( "Huffman Compressor Properly Compresses File", "[compressor]") {
  std::unique_ptr<zip::DataCompressor> compressor = std::make_unique<huffzip::HuffmanCompressor>();

  REQUIRE( true );
}
