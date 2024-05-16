CC = gcc
CPPFLAGS = -Iincludes -Isrc
CFLAGS = -Wall -Wextra -Werror
LDLIBS = -lm
LIB_DIR = libs

SRC = src
OBJ = obj
BIN = rt
LIBS = -L$(LIB_DIR) -lmlx_Linux -lXext -lX11 -lm -lbsd
MKDIR = mkdir -p
SRCs := $(shell find $(SRC) -name "*.c")
OBJs := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCs))

all: $(BIN)

$(BIN): $(OBJs) $(LIB_DIR)/libmlx_Linux.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJs) $(LIBS) -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -R $(BIN)
	$(RM) -R $(OBJ)

re: clean all
