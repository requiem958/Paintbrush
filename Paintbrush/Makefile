WORKDIR = `pwd`

CC = clang
INC = -Iincludes
CFLAGS = -Wextra -Wall --std=c99 -g `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`  -lSDL2_image -lSDL2_gfx -lconfig
INC_DIR = includes
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

EXEC = $(BIN_DIR)/Paintbrush

all: $(EXEC)

../Docs/html/*: $(SRC_DIR)/*.c $(INC_DIR)/*.h
../Docs/latex/*: $(SRC_DIR)/*.c $(INC_DIR)/*.h

documentation: ../Docs/html/* ../Docs/latex/*
	doxygen ../Doxyfile

clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC) $(SRC_DIR)/*.c~ $(INC_DIR)/*.h~

$(OBJ_DIR)/quit.o: $(SRC_DIR)/quit.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/fonctions.o: $(SRC_DIR)/fonctions.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_fonctions.o: $(SRC_DIR)/game_fonctions.c $(OBJ_DIR)/players.o $(OBJ_DIR)/fonctions.o
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/players.o: $(SRC_DIR)/players.c $(OBJ_DIR)/fonctions.o
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/Paintbrush: 	$(SRC_DIR)/main.c $(OBJ_DIR)/quit.o $(OBJ_DIR)/fonctions.o \
			$(OBJ_DIR)/game_fonctions.o $(OBJ_DIR)/players.o
	$(CC) $(INC) $(CFLAGS) $(LDFLAGS) $^ -o $@
