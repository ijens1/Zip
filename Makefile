CXX = g++
current_dir = $(shell pwd)
include_dir = $(current_dir)/src/include
CXXFLAGS = -std=c++14 -Wall -g -MMD -I $(include_dir)
EXEC_1 = cpress
EXEC_2 = dpress
INCLUDE_OBJECTS = src/include/subject.o src/include/basic_display_service.o src/include/bit_io.o
OBJECTS_1 = src/cpressmain.o src/compressors/huffzip/huffman_compressor.o
OBJECTS_2 = src/dpressmain.o src/decompressors/huffunzip/huffman_decompressor.o

all: ${EXEC_1} ${EXEC_2}

DEPENDS_1 = ${OBJECTS_1:.o=.d}
DEPENDS_2 = ${OBJECTS_2:.o=.d}
DEPENDS_INCLUDE = ${INCLUDE_OBJECTS:.o=.d}

${EXEC_1}: ${OBJECTS_1} ${INCLUDE_OBJECTS}
	${CXX} ${OBJECTS_1} ${INCLUDE_OBJECTS} -o ${EXEC_1} ${CXXENDFLAGS}

${EXEC_2}: ${OBJECTS_2} ${INCLUDE_OBJECTS}
	${CXX} ${OBJECTS_2} ${INCLUDE_OBJECTS} -o ${EXEC_2} ${CXXENDFLAGS}

-include ${DEPENDS_1}
-include ${DEPENDS_2}
-include ${DEPENDS_INCLUDE}

.PHONY: clean

clean:
	rm ${EXEC_1} ${EXEC_2} ${OBJECTS_1} ${OBJECTS_2} ${INCLUDE_OBJECTS} ${DEPENDS_1} ${DEPENDS_2} ${DEPENDS_INCLUDE}
