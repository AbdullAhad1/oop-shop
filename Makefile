CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -I./include

SRC = src/User.cpp \
      src/Customer.cpp \
      src/Admin.cpp \
      src/Product.cpp \
      src/Cart.cpp \
      src/Order.cpp \
      src/Inventory.cpp \
      src/UI.cpp \
      src/main.cpp

OBJ = $(SRC:src/%.cpp=build/%.o)
TARGET = build/shop

all: $(TARGET)

build:
	mkdir -p build

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)

start: run

.PHONY: all clean run start
