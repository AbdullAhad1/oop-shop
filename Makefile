CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -I./include

SRC = src/sayfaz/User.cpp \
      src/sayfaz/Customer.cpp \
      src/sayfaz/Admin.cpp \
      src/araf/Product.cpp \
      src/araf/Cart.cpp \
      src/araf/Order.cpp \
      src/araf/Inventory.cpp \
      src/ahad/UI.cpp \
      src/ahad/main.cpp

OBJ = $(SRC:src/%.cpp=build/%.o)
TARGET = build/shop

all: $(TARGET)

build:
	mkdir -p build/ahad build/sayfaz build/araf

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
