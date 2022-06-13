# Directories set up
BINDIR = bin/
OBJDIR = obj/
SRCDIR = src/

# Executable name
TARGET = $(BINDIR)huffman

# Project set up, compiler flags and linker flags
CC = gcc -fsanitize=address
CFLAGS = -g -O3 -Wall -Wno-unused-result
LFLAGS = -lm

# Files set up
SRC := $(wildcard $(SRCDIR)*.c)
OBJ := $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

# Compile binary and object files and build target
all: $(TARGET) objclean
	
$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(LFLAGS) $^ -o $@ 
	@echo "Compilation and linking completed !"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean project directory
.PHONY: clean
clean:
	@rm -rf $(BINDIR) $(OBJDIR)
	@echo "Cleanup completed !"

objclean:
	@rm -rf $(OBJDIR)