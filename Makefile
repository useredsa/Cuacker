# Location of header files
INC_DIR=include
# Location of source files
SRC_DIR=src
# Source Files Extensions
EXT=.cpp
# Location of objetct files
OBJ_DIR=obj

# Main file.
MAIN=mooshak/main
TARGET=$(MAIN)$(EXT)


CC=g++ # Compiler
PPFLAGS=-I $(INC_DIR)/ # Preprocessor flags
FLAGS=-Wall -std=c++11 -O2 # Compiler Flags
COMMAND=$(CC) -c $(SRC_DIR)/$(basename $(notdir $@))$(EXT) $(PPFLAGS) $(FLAGS) -o $@

.PHONY: clean test tar pre_file pos_file

mooshak: pre_file a.out pos_file

a.out: $(TARGET) $(OBJ_DIR)/date.o $(OBJ_DIR)/cuac.o $(OBJ_DIR)/database.o $(OBJ_DIR)/interpreter.o
	$(CC) $^ $(PPFLAGS) $(FLAGS) -o a.out

$(OBJ_DIR)/date.o: $(SRC_DIR)/date$(EXT) $(INC_DIR)/date.h
	$(COMMAND)

$(OBJ_DIR)/cuac.o: $(SRC_DIR)/cuac$(EXT) $(INC_DIR)/cuac.h $(INC_DIR)/date.h
	$(COMMAND)

$(OBJ_DIR)/database.o:  $(SRC_DIR)/database$(EXT) $(INC_DIR)/database.h \
			$(INC_DIR)/date.h $(INC_DIR)/cuac.h $(INC_DIR)/avl_tree.h $(INC_DIR)/avl_tree.hpp \
			$(INC_DIR)/hash_set.h $(INC_DIR)/hash_set.hpp
	$(COMMAND)

$(OBJ_DIR)/interpreter.o: $(SRC_DIR)/interpreter$(EXT) $(INC_DIR)/interpreter.h $(INC_DIR)/database.h
	$(COMMAND)

# Super hardcode for mooshak
pre_file:
	@mkdir obj 2>/dev/null; true;

pos_file:


clean:
	@rm $(OBJ_DIR)/*.o

test: a.out
	@if ! ./a.out <input 2>/dev/null | diff -q - compare_output;\
	then\
		printf "\n\n___STDOUT___\n";\
		./a.out <input 2>/dev/null;\
		printf "\n\n___STDERR___\n";\
		./a.out <input >/dev/null;\
	fi

tar: clean test
	@tar -cf$(basename $(TARGET)).tar $(INC_DIR) $(TARGET) $(SRC_DIR) Makefile
