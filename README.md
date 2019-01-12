# Zip project
Hi. This is a basic compression exercise (emphasis on basic) to help me learn
about how simple data compression algorithms work.

At the moment, this repo includes just huffman coding, although I'm thinking 
about possibly doing arithmetic coding at some point. I've followed the basic
steps laid out in [wikipedia](https://en.wikipedia.org/wiki/Huffman_coding) for
the coding algorithm.

Basic usage for huffman coding is 
```shell
$ make
$ ./hz <your_file.file_extension>
```
This should produce a file called `your_file.hz` in the current directory. This is the compressed data.
(You might notice that the compression is usually about 50% or less, haven't
done serious experimentation on that number though).

To decompress, simply run the other half of this exercise (this step assumes
you haven't `make clean`'d):
```shell
$ ./huz <your_file.hz>
```

This should produce your original file in the current directory.
