CXX = g++
current_dir = $(shell pwd)
include_dir = $(current_dir)/src/include
CXXFLAGS = -std=c++17 -Wall -g -MMD -I $(include_dir)
EXEC_1 = cpress
EXEC_2 = dpress
EXEC_3 = testsuite
GENERAL_INCLUDE_OBJECTS = src/include/subject.o src/include/basic_display_service.o src/include/bit_io.o src/include/model.o
CPRESS_OBJECTS = src/compressors/huffzip/huffman_compressor.o src/compressors/arithzip/arithmetic_compressor.o
DPRESS_OBJECTS = src/decompressors/huffunzip/huffman_decompressor.o src/decompressors/arithunzip/arithmetic_decompressor.o
OBJECTS_1 = src/cpressmain.o
OBJECTS_2 = src/dpressmain.o
OBJECTS_3 = src/testmain.o src/test/include/bit_io_test.o src/test/include/model_test.o src/test/coding/huffman_test.o src/test/coding/arithmetic_test.o

all: ${EXEC_1} ${EXEC_2} ${EXEC_3}

DEPENDS_1 = ${OBJECTS_1:.o=.d}
DEPENDS_2 = ${OBJECTS_2:.o=.d}
DEPENDS_3 = ${OBJECTS_3:.o=.d}
DEPENDS_INCLUDE = ${GENERAL_INCLUDE_OBJECTS:.o=.d}

${EXEC_1}: ${OBJECTS_1} ${CPRESS_OBJECTS} ${GENERAL_INCLUDE_OBJECTS}
	${CXX} ${OBJECTS_1} ${CPRESS_OBJECTS} ${GENERAL_INCLUDE_OBJECTS} -o ${EXEC_1} ${CXXFLAGS}

${EXEC_2}: ${OBJECTS_2} ${DPRESS_OBJECTS} ${GENERAL_INCLUDE_OBJECTS}
	${CXX} ${OBJECTS_2} ${DPRESS_OBJECTS} ${GENERAL_INCLUDE_OBJECTS} -o ${EXEC_2} ${CXXFLAGS}

${EXEC_3}: ${OBJECTS_3} ${CPRESS_OBJECTS} ${DPRESS_OBJECTS} ${GENERAL_INCLUDE_OBJECTS}
	${CXX} ${OBJECTS_3} ${CPRESS_OBJECTS} ${DPRESS_OBJECTS} ${GENERAL_INCLUDE_OBJECTS} -o ${EXEC_3} ${CXXFLAGS}

-include ${DEPENDS_1}
-include ${DEPENDS_2}
-include ${DEPENDS_3}
-include ${DEPENDS_INCLUDE}

.PHONY: clean

clean:
	rm ${EXEC_1} ${EXEC_2} ${EXEC_3} ${OBJECTS_1} ${OBJECTS_2} ${OBJECTS_3} ${CPRESS_OBJECTS} ${DPRESS_OBJECTS} ${GENERAL_INCLUDE_OBJECTS} ${DEPENDS_1} ${DEPENDS_2} ${DEPENDS_3} ${DEPENDS_INCLUDE}
