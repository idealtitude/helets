# Basic vars & flags
CXX=clang++
CXXFLAGS=-std=c++20 -g -O0 -W -Wall -Werror -Wextra -Wshadow -pthread -Wno-sign-compare -Wconversion -Wno-unused-function -Wpedantic -pedantic -pedantic-errors
LDFLAGS=

# Directories & other
BINNAME=my_language
BINDIR=. # Output binary to current directory
SRCDIR=src # Source files in src directory
OBJDIR=build # Object files in build directory

# Define source files specifically, now with path
LEXER_SRC=$(SRCDIR)/lexer.l
PARSER_SRC=$(SRCDIR)/parser.y
MAIN_SRC=$(SRCDIR)/main.cpp

# Define object files specifically, with path to OBJDIR
LEXER_OBJ=$(OBJDIR)/lexer.o
PARSER_OBJ=$(OBJDIR)/parser.o
MAIN_OBJ=$(OBJDIR)/main.o

OBJS=$(LEXER_OBJ) $(PARSER_OBJ) $(MAIN_OBJ)

BIN=$(BINDIR)/$(BINNAME)

all: $(BIN)

release: CXXFLAGS=-std=c++20 -Wall -O2 -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(OBJS) $(OBJDIR) # Add OBJDIR as a dependency
        $(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(LEXER_OBJ): $(LEXER_SRC) $(OBJDIR) # Add OBJDIR as a dependency
        flex $(LEXER_SRC)
        $(CXX) $(CXXFLAGS) -c lexer.c -o $@ # lexer.c is created in the current directory

$(PARSER_OBJ): $(PARSER_SRC) $(OBJDIR) # Add OBJDIR as a dependency
        bison -d $(PARSER_SRC)
        $(CXX) $(CXXFLAGS) -c parser.tab.c -o $@ # parser.tab.c is created in the current directory

$(MAIN_OBJ): $(MAIN_SRC) $(OBJDIR) # Add OBJDIR as a dependency
        $(CXX) $(CXXFLAGS) -c $(MAIN_SRC) -o $@

$(OBJDIR): # Rule to create the object directory
        mkdir -p $@

clean:
        $(RM) $(BIN) $(OBJDIR) lexer.c parser.tab.c parser.tab.h # Remove OBJDIR

cleanall: clean