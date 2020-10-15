# Zip project
Hi. This is an exercise to help me learn how basic data compression algorithms work.

I've followed the
steps laid out in [wikipedia](https://en.wikipedia.org/wiki/Huffman_coding) for
the huffman algorithm.

I've read multiple sources to help understand arithmetic coding:
[This paper](https://www.cc.gatech.edu/~jarek/courses/7491/Arithmetic2.pdf) was
pretty useful to understand the basic concept.
I've also spent time looking at [this
repo](https://github.com/nayuki/Reference-arithmetic-coding) to help fix one off
errors.

Usage is as follows
```shell
$ make
$ ./cpress -m <coding_method> <input_file_name> <output_file_name>
```
`<coding_method>` can be one of `huffman` or `arithmetic`.

To decompress, simply run the other half of this exercise:
```shell
$ ./dpress -m <coding_method> <input_file_name> <output_file_name>
```

The `<coding_method>` should be the same as the one provided in the compression

This should produce a file with the original contents of the compressed file

## Test Suite

There is a unit testing suite for this project. If you'd like to run it, just run `./testsuite` after `make`, adding `-s` if you'd like more verbose results (includes info about tests that passed).

This assumes you've added [`catch.hpp`](https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp) to your `usr/local/include`.
