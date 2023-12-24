CXX := g++
CXXFLAGS := -std=c++11
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
ZMQ_LIB := -lzmq
INCLUDE_DIR := -I../include  # Add this line to specify the include directory

# Source files in the current directory
SRC_CURRENT := GameServer.cpp
# Source files in the 'src' directory
SRC_SRC := ../src/Timeline.cpp

# Combine source files
SRC := $(SRC_CURRENT) $(SRC_SRC)
OBJ := $(SRC:.cpp=.o)

TARGET := server

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) $^ -o $@ $(SFML_LIBS) $(ZMQ_LIB)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
