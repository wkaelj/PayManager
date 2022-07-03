CXXFLAGS= `pkg-config --cflags gtkmm-4.0` -g -std=c++17 -Wall -Wno-reorder
LIBS= `pkg-config --libs gtkmm-4.0`

# build folder
BIN=bin

SOURCES= $(wildcard src/*.cpp) # $(wildcard src/*.hpp)
OBJS=$(SOURCES:.cpp=.o)

# exectutable name
BINARY=PayManager

# chosen compiler
CXX ?= g++

.PHONY: clean run phony all

all: dirs $(BINARY)

# run executable
run:
	G_ENABLE_DIAGNOSTIC=1 ./$(BIN)/$(BINARY)

debug: all
	gdb ./$(BIN)/$(BINARY)

# directories for compiler
dirs:
	mkdir -p ./$(BIN)

# link objs into executable
$(BINARY): $(OBJS)
	$(info OBJS is $(OBJS))
	$(CC) $(CXXFLAGS) -o $(BIN)/$(BINARY) $^ $(LIBS)

# compile src to objs
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJS)
