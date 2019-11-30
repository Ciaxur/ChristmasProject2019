CC = g++
FLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
SRC_DIR = src
FILES = *.cc
OUT = app

GTK_SANDBOX_DIR = $(SRC_DIR)/include/gtk-sandbox/src/
GTK_SANDBOX_INCLUDES = $(GTK_SANDBOX_DIR)/ContextArea.cc -I./$(GTK_SANDBOX_DIR)

build:
	$(CC) $(SRC_DIR)/$(FILES) $(GTK_SANDBOX_INCLUDES) -o $(OUT) $(FLAGS) 

init-git-submodules:
	git submodule init
	git submodule sync
	git submodule update --recursive
