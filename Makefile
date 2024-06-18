CFLAGS=`/home/linuxbrew/.linuxbrew/bin/sdl2-config --cflags --libs` -std=c++23 -ldl -lm #-lSDL2_ttf
all:
	clear
	g++-14 ./src/*.cpp ./src/**/*.cpp ./src/**/**/*.cpp -o ./out/main $(CFLAGS)
