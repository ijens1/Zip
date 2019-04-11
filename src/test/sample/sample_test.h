#ifndef SAMPLE_TEST_H
#define SAMPLE_TEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace ziptest {
  class SampleTest : public CppUnit::TestFixture {
      CPPUNIT_TEST_SUITE(SampleTest);
      CPPUNIT_TEST(testEquality);
      CPPUNIT_TEST(testAddition);
      CPPUNIT_TEST_SUITE_END();

      int *a, *b;
    public:
      void setUp() {
        a = new int;
        *a = 5;
        b = new int;
        *b = 10;
      }

      void tearDown() {
        delete a;
        delete b;
      }

      void testEquality();

      void testAddition();
  };
}

#endif
