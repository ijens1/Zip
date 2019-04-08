#include <cppunit/ui/text/TestRunner.h>
#include "test/sample/sample_test.h"

int main(int argc, char** argv) {
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(ziptest::SampleTest::suite());
  runner.run();
  return 0;
}
