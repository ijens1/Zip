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

void zip::BitIn::pullBit(unsigned char& char_bit, std::istream& in) {
  if (curr_bit_index == 7) {
    curr_bit_index = -1;
  }
  if (curr_bit_index == -1) {
    char next_byte;
    curr_byte = (in.get(next_byte)) ? next_byte : 0;
  }
  curr_bit_index++;
  unsigned char curr_byte_u = curr_byte;
  char_bit = ((curr_byte_u >> (7 - curr_bit_index)) & 1);
}

void zip::BitIn::pullByte(unsigned char& c, std::istream& in) {
  c = 0;
  for (int i = 7; i >= 0; --i) {
    unsigned char b;
    pullBit(b, in);
    c |= (b << i);
  }
}
