#ifndef SAMPLE_TEST_H
#define SAMPLE_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

namespace ziptest {

  class SampleTest : public CppUnit::TestFixture {
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

      static CppUnit::Test *suite() {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("SampleTest");

        suiteOfTests->addTest(new CppUnit::TestCaller<SampleTest>(
              "testEquality",
              &SampleTest::testEquality));

        suiteOfTests->addTest(new CppUnit::TestCaller<SampleTest>(
              "testAddition",
              &SampleTest::testAddition));

        return suiteOfTests;
      }
  };
}

#endif
