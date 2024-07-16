FLAGS=`/home/linuxbrew/.linuxbrew/bin/sdl2-config --cflags --libs` -std=c++23 -ldl -lm -lSDL2_image #-lSDL2_ttf
SRC_DIR=./src
SRCS=$(shell find ./src -name *.cpp -not -type d | xargs echo)
HEADERS=$(shell find ./src -name *.hpp -not -type d | xargs echo)
BIN=./out/main
$(BIN): $(SRCS) $(HEADERS)
	clear
	g++-14 $(SRCS) -o $@ $(FLAGS)