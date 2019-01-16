#ifndef INCLUDE_BIT_IO_H_
#define INCLUDE_BIT_IO_H_

#include <istream>
#include <ostream>
#include <string>

namespace zip {

  // Class doesn't guarantee that there won't be trailing bits after making
  // a call to output(std::string) UNLESS the length of the provided string is
  // a multiple of 8
  class BitOut {
    public:
      // Outputs entire string.
      // Assumes string is a string of '0's and '1's.
      void putBin(const std::string&, std::ostream&);
  };

  class BitIn {
      char curr_byte = 0;
      int curr_bit_index = 0;

    public:
      // Reads in next bit into first bit of provided char
      void pullBit(char&, std::istream&);
  };
}

#endif // INCLUDE_BIT_IO_H_
