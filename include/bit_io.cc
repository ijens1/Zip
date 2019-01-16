#include "bit_io.h"

void zip::BitOut::putBin(const std::string& bit_str, std::ostream& out) {
  size_t i = 0;
  for (; i < bit_str.size(); i += 8) {
    char next_byte = 0;
    for (size_t j = i; j < i + 8 && j < bit_str.size(); ++j) {
      next_byte |= (bit_str[j] - '0') << (8 - (j - i) - 1);
    }
    out << next_byte;
  }
}

void zip::BitIn::pullBit(char& char_bit, std::istream& in) {
  if (curr_bit_index == 7) {
    in >> curr_byte;
    curr_bit_index = 0;
  } else {
    curr_bit_index++;
  }
  char_bit = ((curr_byte >> (7 - curr_bit_index)) | 1);
}
