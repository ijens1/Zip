#include "bit_io_test.h"
#include <iostream>

void ziptest::BitIoTest::bitInPullBitTest() {
    unsigned char next_char;
    std::string final_bin_str = "";
    for (unsigned int i = 0; i < in_message.length() * 8; ++i) {
      bin->pullBit(next_char, *iss);
      final_bin_str.push_back(char(next_char + 48));
    }
    CPPUNIT_ASSERT(final_bin_str == "010010000110010101101100011011000110111100100000010101110110111101110010011011000110010000100001");
}
