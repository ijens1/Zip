CXX = g++
current_dir = $(shell pwd)
include_dir = $(current_dir)/src/include
CXXFLAGS = -std=c++14 -Wall -g -MMD -I $(include_dir) -lcppunit
EXEC_1 = cpress
EXEC_2 = dpress
EXEC_3 = testsuite
INCLUDE_OBJECTS = src/include/subject.o src/include/basic_display_service.o src/include/bit_io.o src/include/model.o
OBJECTS_1 = src/cpressmain.o src/compressors/huffzip/huffman_compressor.o src/compressors/arithzip/arithmetic_compressor.o
OBJECTS_2 = src/dpressmain.o src/decompressors/huffunzip/huffman_decompressor.o src/decompressors/arithunzip/arithmetic_decompressor.o
OBJECTS_3 = src/testmain.o src/test/sample/sample_test.o

all: ${EXEC_1} ${EXEC_2} ${EXEC_3}

DEPENDS_1 = ${OBJECTS_1:.o=.d}
DEPENDS_2 = ${OBJECTS_2:.o=.d}
DEPENDS_3 = ${OBJECTS_3:.o=.d}
DEPENDS_INCLUDE = ${INCLUDE_OBJECTS:.o=.d}

${EXEC_1}: ${OBJECTS_1} ${INCLUDE_OBJECTS}
	${CXX} ${OBJECTS_1} ${INCLUDE_OBJECTS} -o ${EXEC_1} ${CXXENDFLAGS}

${EXEC_2}: ${OBJECTS_2} ${INCLUDE_OBJECTS}
	${CXX} ${OBJECTS_2} ${INCLUDE_OBJECTS} -o ${EXEC_2} ${CXXENDFLAGS}

${EXEC_3}: ${OBJECTS_3} ${INCLUDE_OBJECTS}
	${CXX} ${OBJECTS_3} ${INCLUDE_OBJECTS} -o ${EXEC_3} ${CXXENDFLAGS}

-include ${DEPENDS_1}
-include ${DEPENDS_2}
-include ${DEPENDS_3}
-include ${DEPENDS_INCLUDE}

.PHONY: clean

clean:
	rm ${EXEC_1} ${EXEC_2} ${EXEC_3} ${OBJECTS_1} ${OBJECTS_2} ${OBJECTS_3} ${INCLUDE_OBJECTS} ${DEPENDS_1} ${DEPENDS_2} ${DEPENDS_3} ${DEPENDS_INCLUDE}
