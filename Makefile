CFLAGS=`sdl2-config --cflags`
LFLAGS=`sdl2-config --libs` #-lSDL2_ttf
all:
	clear
	g++ ./src/*.cpp ./src/**/*.cpp ./src/**/**/*.cpp -o ./out/main $(CFLAGS) $(LFLAGS)
