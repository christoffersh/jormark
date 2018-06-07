TARGET := jormark

# Compiler options
CC := g++ # This is the main compiler
SRCEXT := cpp # source file extension 
CFLAGS := -g -MMD -std=c++14 -O0
LIB := 

# Directories
SRCDIR := .
BUILDDIR := build
TARGETDIR := bin

# Main program requirements 
MAIN_SRC := $(SRCDIR)/main.cpp
MAIN_OBJ := $(BUILDDIR)/main.o
MAIN_DEPS := $(BUILDDIR)/main.d
MAIN_TARGET := $(TARGETDIR)/$(TARGET)

# Common requirements
SRC := $(shell find . -type f -name "*.cpp" |grep -v main)
OBJ := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC))
DEPS := $(OBJ:.o=.d) 

ALL_DEPS := $(DEPS) $(MAIN_DEPS) $(TEST_DEPS)

.PHONY: all program
all: program 

#------------ Main Program -----------------
# Action for making main program
program: $(MAIN_TARGET)

# Link rule
$(MAIN_TARGET):$(OBJ) $(MAIN_OBJ)
	@echo ' Linking objects..' $(OBJ)
	@mkdir -p $(TARGETDIR)
	$(CC) $(CFLAGS) $(LIB) $(INC) $^ -o $@ 

-include $(ALL_DEPS)
# Compile rule
$(BUILDDIR)/%.o: %.cpp 
	@echo " Compiling object: "$@ 
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

#-------- Non-compile actions ---------------
clean:
	@echo ' Cleaning...'
	@rm -r $(BUILDDIR)
	@rm -r $(TARGETDIR)
