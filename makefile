CXXFLAGS= -g -Og -std=c++17 -Wall -Wextra `pkg-config --cflags gtkmm-3.0` -I/usr/include/gtkmm-3.0
LFLAGS= -lstdc++ `pkg-config --libs gtkmm-3.0`

# build folder
BIN=bin

SOURCES= $(wildcard src/*.cpp) $(wildcard src/*.hpp)
OBJS=$(SOURCES:.cpp=.o)

# exectutable name
BINARY=PayManager

# chosen compiler
CXX=cc

.PHONY: clean

all: dirs $(BINARY)
	rm -rf ./$(BIN)/ui
	cp -r ./ui ./bin/ui


# run executable
run:
	./$(BIN)/$(BINARY)

# directories for compiler
dirs:
	mkdir -p ./$(BIN)

# link objs into executable
$(BINARY): $(OBJS)
	$(info OBJS is $(OBJS))
	$(CC) -o $(BIN)/$(BINARY) $^ $(LFLAGS)

# compile src to objs
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJS)
