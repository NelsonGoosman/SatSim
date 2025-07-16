# Install with: sudo apt-get install libcurl4-openssl-dev
CXX := g++
CXXFLAGS := -Wall -Isrc -g -O0 -ggdb3
LDFLAGS := -lcurl

# Find all .cpp files in current directory and src subdirectories
SRC := $(wildcard *.cpp) $(wildcard src/**/*.cpp)
OUT := satsim

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)