WORKDIR = `pwd`

CC = gcc
<<<<<<< HEAD
CXX = g++
AR = ar
LD = ld
WINDRES = windres

INC = -Iincludes
CFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Wmain -pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -ansi -std=c99
RESINC = 
LIBDIR = -Llibs -L/lib64 -L/lib/x86_64-linux-gnu
LIB = 
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_gfx -lconfig
SRC =

INC_DEBUG = $(INC)
SRC_DEBUG = $(SRC)
CFLAGS_DEBUG = $(CFLAGS)
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/Paintbrush

INC_RELEASE = $(INC)
SRC_RELEASE = $(SRC)
CFLAGS_RELEASE = $(CFLAGS)
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS)
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/Paintbrush

OBJ_DEBUG = $(OBJDIR_DEBUG)/quit.o $(OBJDIR_DEBUG)/players.o $(OBJDIR_DEBUG)/painters.o $(OBJDIR_DEBUG)/main.o $(OBJDIR_DEBUG)/inits.o $(OBJDIR_DEBUG)/game_fonctions.o $(OBJDIR_DEBUG)/fonctions.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/quit.o $(OBJDIR_RELEASE)/players.o $(OBJDIR_RELEASE)/painters.o $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/inits.o $(OBJDIR_RELEASE)/game_fonctions.o $(OBJDIR_RELEASE)/fonctions.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)
=======

INC = -Iincludes
CFLAGS = -Wshadow -Winit-self \
	 -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
	 -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
	 -Wswitch-default -Wmain -pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -ansi \
	 -std=c99 -g `sdl2-config --cflags`
>>>>>>> aa93215c9937fad2f1dbfc3f3ce299ed4e1e5e8b

LIBDIR = -L/lib64 -L/lib/x86_64-linux-gnu
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_gfx -lconfig
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
	$(CC) $(INC) $(CFLAGS) $(LIBDIR) $(LDFLAGS) $^ -o $@
