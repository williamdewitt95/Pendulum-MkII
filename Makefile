CC = g++
CFLAGS = -std=gnu++0x
COPTS = -O2
LIBS = -lGL -lGLU -lglut -ljpeg -lpng libSOIL.a -lGLEW
BUILD_DIR   = build

OBJS = house.o matrixWork.o myUtils.o polygon.o vertex.o globals.o table.o pendulum.o main.o
BUILD_OBJS  = $(addprefix $(BUILD_DIR)/, $(OBJS))


all : build pendulumMKII

build :
	mkdir build

pendulumMKII : $(BUILD_OBJS)
	$(CC) $(CFLAGS) -o pendulumMKII $(BUILD_OBJS) $(LIBS)

$(BUILD_DIR)/main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp -c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/globals.o : globals.cpp globals.h
	$(CC) $(CFLAGS) $(COPTS) globals.cpp -c -o $(BUILD_DIR)/globals.o

$(BUILD_DIR)/house.o : house.cpp house.h
	$(CC) $(CFLAGS) $(COPTS) house.cpp -c -o $(BUILD_DIR)/house.o

$(BUILD_DIR)/matrixWork.o : matrixWork.cc matrixWork.h
	$(CC) $(CFLAGS) $(COPTS) matrixWork.cc -c -o $(BUILD_DIR)/matrixWork.o

$(BUILD_DIR)/myUtils.o : myUtils.cpp myUtils.h
	$(CC) $(CFLAGS) $(COPTS) myUtils.cpp -c -o $(BUILD_DIR)/myUtils.o

$(BUILD_DIR)/polygon.o : polygon.cpp polygon.h
	$(CC) $(CFLAGS) $(COPTS) polygon.cpp -c -o $(BUILD_DIR)/polygon.o

$(BUILD_DIR)/vertex.o : vertex.cpp vertex.h
	$(CC) $(CFLAGS) $(COPTS) vertex.cpp -c -o $(BUILD_DIR)/vertex.o

$(BUILD_DIR)/table.o : table.cpp table.h
	$(CC) $(CFLAGS) $(COPTS) table.cpp -c -o $(BUILD_DIR)/table.o

$(BUILD_DIR)/pendulum.o : pendulum.cpp pendulum.h
	$(CC) $(CFLAGS) $(COPTS) pendulum.cpp -c -o $(BUILD_DIR)/pendulum.o


.PHONY: clean distclean pristine

clean:
	rm -f build/*.o
	rm -f pendulumMKII

pristine:
	rm -rf build
	rm -f pendulumMKII
	touch *

distclean: pristine