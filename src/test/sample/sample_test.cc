#include "sample_test.h"

void ziptest::SampleTest::testEquality() {
    CPPUNIT_ASSERT(*a != *b);
}

void ziptest::SampleTest::testAddition() {
    CPPUNIT_ASSERT(*a + *b == 15);
}
