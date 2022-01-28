# Project set up, compiler flags and linker flags
CC =gcc -fsanitize=address
CFLAGS =-g -std=c11 -O3 -Wall -Wno-unused-result
LFLAGS =-lm

# Directories set up
BINDIR =bin/
OBJDIR =obj/
SRCDIR =src/

# Files set up
SRC := $(wildcard $(SRCDIR)*.c)
OBJ := $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

# Executable name
TARGET =$(BINDIR)huffman

# Compile binary and object files and build target
all: $(TARGET) objclean
	
$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(LFLAGS) $^ -o $@ 
	@echo "Compilation and linking completed !"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Installation in /usr/local/bin for global usage
.PHONY: install
install: all
	sudo cp $(TARGET) /usr/local/bin

uninstall:
	sudo rm /usr/local/bin/$(TARGET)

# Clean project directory
.PHONY: clean
clean:
	@rm -rf $(BINDIR) $(OBJDIR)
	@echo "Cleanup completed !"

objclean:
	@rm -rf $(OBJDIR)