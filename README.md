# Zip project
Hi. This is a basic compression exercise (emphasis on basic) to help me learn
about how simple data compression algorithms work.

At the moment, the complete zipping methods this repo includes just huffman
coding, although I'm working on arithmetic coding at the moment. I've followed the basic
steps laid out in [wikipedia](https://en.wikipedia.org/wiki/Huffman_coding) for
the huffmain coding algorithm.

Usage for huffman coding is 
```shell
$ make
$ ./cpress -m huffman <your_file.file_extension>
```
This should produce a file called `your_file.hz` in the current directory. This is the compressed data.
(You might notice that the compression is usually about 50% or less, haven't
done serious experimentation on that number though).

To decompress, simply run the other half of this exercise (this step assumes
you haven't `make clean`'d):
```shell
$ ./dpress <your_file.hz>
```

This should produce your original file in the current directory.

## Options
### `-m` Option
The current values available for this option are `huffman` and `arithmetic`.
