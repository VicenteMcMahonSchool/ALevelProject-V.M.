FLAGS=`/home/linuxbrew/.linuxbrew/bin/sdl2-config --cflags --libs` -std=c++23 -ldl -lm -lSDL2_image #-lSDL2_ttf
SRC_DIR=./src
SRCS=$(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/**/**/*.cpp)
HEADERS=$(wildcard $(SRC_DIR)/*.hpp) $(wildcard $(SRC_DIR)/**/*.hpp) $(wildcard $(SRC_DIR)/**/**/*.hpp)
all: $(SRCS) $(HEADERS)
	clear
	g++-14 $(SRCS) -o ./out/main $(FLAGS)