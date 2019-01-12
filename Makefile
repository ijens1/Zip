CXX = g++
current_dir = $(shell pwd)
include_dir = $(current_dir)/include
CXXFLAGS = -std=c++14 -Wall -g -MMD -I $(include_dir)
EXEC_1 = hz
EXEC_2 = huz
OBJECTS_1 = huffzip/main.o huffzip/huffman_compressor.o include/subject.o include/basic_display_service.o
OBJECTS_2 = huffunzip/main.o

all: ${EXEC_1} ${EXEC_2}

DEPENDS_1 = ${OBJECTS_1:.o=.d}
DEPENDS_2 = ${OBJECTS_2:.o=.d}

${EXEC_1}: ${OBJECTS_1}
	${CXX} ${OBJECTS_1} -o ${EXEC_1} ${CXXENDFLAGS}

${EXEC_2}: ${OBJECTS_2}
	${CXX} ${OBJECTS_2} -o ${EXEC_2} ${CXXENDFLAGS}

-include ${DEPENDS_1}
-include ${DEPENDS_2}

.PHONY: clean

clean:
	rm ${EXEC_1} ${EXEC_2} ${OBJECTS_1} ${OBJECTS_2} ${DEPENDS_1} ${DEPENDS_2}
