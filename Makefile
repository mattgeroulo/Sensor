CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17
LDFLAGS  := -lgpiod

TARGET := main
SRC    := main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
