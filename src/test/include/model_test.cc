#include <catch.hpp>
#include <map>
#include "model.h"

TEST_CASE( "Model correctly computes values", "[include]" ) {
  std::string sample_file = "aaabbbcccdd\n";
  std::map<int, int> occurences;
  for (int i = 0; i < sample_file.length(); ++i) {
    ++occurences[sample_file[i]];
  }
  zip::Model model(occurences);

  SECTION( "Total occurences computation" ) {
    REQUIRE( model.getTotalOccurences() == 12);
  }

  SECTION( "Range computation" ) {
    std::pair<int, int> a_range = model.getRange('a');
    std::pair<int, int> b_range = model.getRange('b');
    std::pair<int, int> c_range = model.getRange('c');
    std::pair<int, int> d_range = model.getRange('d');
    std::pair<int, int> newline_range = model.getRange('\n');

    REQUIRE( newline_range.first == 0 );
    REQUIRE( newline_range.second == 1 );
    REQUIRE( a_range.first == 1 );
    REQUIRE( a_range.second == 4 );
    REQUIRE( b_range.first == 4 );
    REQUIRE( b_range.second == 7 );
    REQUIRE( c_range.first == 7 );
    REQUIRE( c_range.second == 10 );
    REQUIRE( d_range.first == 10 );
    REQUIRE( d_range.second == 12 );
  }

  SECTION( "Character retrievals" ) {
     int first_character = model.getCharacter(0);
     int second_character = model.getCharacter(5);
     int third_character = model.getCharacter(11);

     REQUIRE( char(first_character) == '\n' );
     REQUIRE( char(second_character) == 'b' );
     REQUIRE( char(third_character) == 'd' );
  }
}

