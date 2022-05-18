# COMPILER FLAGS
CC=gcc
CFLAGS=-I. -Wall -Wextra -g
#-U_FORTIFY_SOURCE -fno-omit-frame-pointer -fno-common -fsanitize=address -fsanitize-recover=address
VG_FLAGS=--tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes
LIBS=-lcrypto -lssl -lpthread
# -fsanitize=address
INCLUDE_PATH=-Iinclude

# WORKING DIRECTORIES
PROJ_DIR := $(realpath $(CURDIR))
SRC_DIR=$(PROJ_DIR)/src
OBJ_DIR=$(PROJ_DIR)/obj
BIN_DIR=$(PROJ_DIR)/bin

# FILES
EXE := antivirus
SRC := $(wildcard $(SRC_DIR)/*/*.c)
OBJ := $(patsubst $(SRC_DIR)/*/%.c, $(OBJ_DIR)/%.o, $(SRC))

# MAIN COMMAND
all: $(EXE)

.PHONY: all



# MAKE EXECUTABLE FROM OBJECTS 
$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $(INCLUDE_PATH) $^ $(LDLIBS) -o $@  $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@

# MAKING BINARY DIRECTORY
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

check_leaks:
	valgrind $(VG_FLAGS) ./$(EXE)

clean:
	@$(RM) -rv $(EXE) $(OBJ_DIR)