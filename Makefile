CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -I./src
FLEX = flex
BISON = bison

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
VERSION=$(shell cat ./VERSION)

# Create directories if they don't exist
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Target executable
TARGET = $(BIN_DIR)/helets-$(VERSION)

# Source files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/AST.cpp
OBJS = $(BUILD_DIR)/lex.yy.o $(BUILD_DIR)/parser.tab.o $(BUILD_DIR)/main.o $(BUILD_DIR)/AST.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/lex.yy.o: $(BUILD_DIR)/lex.yy.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/parser.tab.o: $(BUILD_DIR)/parser.tab.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/lex.yy.cpp: $(SRC_DIR)/lexer.l $(BUILD_DIR)/parser.tab.hpp
	$(FLEX) -o $@ $<

$(BUILD_DIR)/parser.tab.cpp $(BUILD_DIR)/parser.tab.hpp: $(SRC_DIR)/parser.y
	$(BISON) -d -o $(BUILD_DIR)/parser.tab.cpp $<

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/AST.o: $(SRC_DIR)/AST.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

cleanall: clean
	rm -rf $(TARGET)

.PHONY: all clean cleanall
