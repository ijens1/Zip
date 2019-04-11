#ifndef BIT_IO_TEST_H
#define BIT_IO_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <sstream>
#include "bit_io.h"

namespace ziptest {
  class BitIoTest : public CppUnit::TestFixture {
      // Macros to automatically declare static CppUnit::TestSuite *suite()
      CPPUNIT_TEST_SUITE(BitIoTest);
      CPPUNIT_TEST(bitInPullBitTest);
      CPPUNIT_TEST_SUITE_END();

      const std::string in_message = "Hello World!";

      std::stringstream *iss;
      zip::BitIn* bin;
    public:
      void setUp() override {
        iss = new std::stringstream(in_message);
        bin = new zip::BitIn;
      }

      void tearDown() override {
        delete iss;
        delete bin;
      }

      void bitInPullBitTest();
  };
}

#endif
