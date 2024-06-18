CFLAGS=`/home/linuxbrew/.linuxbrew/bin/sdl2-config --cflags --libs` -std=c++23 -ldl -lm #-lSDL2_ttf
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
all: $(SRCS)
	clear
	g++-14 ./src/*.cpp ./src/**/*.cpp ./src/**/**/*.cpp -o ./out/main $(CFLAGS)
