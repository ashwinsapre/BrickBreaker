CXX := g++
CXXFLAGS := -w -std=c++17
SFML_LIBS := -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
ZMQ_LIB := -lzmq
V8_INCLUDE := -I/usr/include/v8
INCLUDE_PATH := -I../include

# Source files (all .cpp files in the ../src directory)
SRC := $(wildcard ../src/*.cpp)
# Add MAIN.cpp to the list of source files
SRC += MAIN.cpp

OBJ := $(SRC:.cpp=.o)

TARGET := client

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(V8_INCLUDE) $(INCLUDE_PATH) $^ -o $@ $(SFML_LIBS) $(ZMQ_LIB) -lv8

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(V8_INCLUDE) $(INCLUDE_PATH) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
