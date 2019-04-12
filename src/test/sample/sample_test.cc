#include <catch.hpp>

TEST_CASE("Passing Sample Test Case", "[sample]") {
  REQUIRE( 1 == 1 );
}

TEST_CASE("Failing Sample Test Case", "[sample]") {
  REQUIRE( 0 == 1 );
}
