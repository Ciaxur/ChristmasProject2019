# COMPILER INFO
CC = g++
FLAGS = `pkg-config gtkmm-3.0 --cflags --libs` --std=c++17

# PROJECT PATHS
SRC_DIR = src
FILES = main.cc
SRC_FILES = $(patsubst %,$(SRC_DIR)/%,$(FILES))
OUT = app

# GTK PATHS
GTK_SANDBOX_DIR = $(SRC_DIR)/include/gtk-sandbox
GTK_SANDBOX_INCLUDES = $(GTK_SANDBOX_DIR)/lib/*.o -I./$(GTK_SANDBOX_DIR)/src

# OBJECT FILES VARS
OBJ_DIR = lib
OBJ_FILES = Stars.cc 
OBJ_INC = $(patsubst %,../$(SRC_DIR)/%,$(OBJ_FILES))



build:
	$(CC) $(SRC_FILES) ./lib/*.o $(GTK_SANDBOX_INCLUDES) -o $(OUT) $(FLAGS)

build-pi:
	$(CC) $(SRC_FILES) ./lib/*.o $(GTK_SANDBOX_INCLUDES) -o $(OUT) $(FLAGS) -lwiringPi -lpthread

build-all:
	make gen-objectFiles
	make build

gen-objectFiles:
	mkdir -p $(OBJ_DIR)
	cd $(OBJ_DIR); $(CC) $(OBJ_INC) -I../$(GTK_SANDBOX_DIR)/src $(FLAGS) -c

clean:
	rm app $(OBJ_DIR)/*.o

init-git-submodules:
	git submodule init
	git submodule sync
	git submodule update --recursive
