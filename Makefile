CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
EXEC = huffzip
OBJECTS = main.o huffman_compressor.o subject.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXENDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
