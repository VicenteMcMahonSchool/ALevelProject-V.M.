CFLAGS=`sdl2-config --cflags`
LFLAGS=`sdl2-config --libs` #-lSDL2_ttf
all:
	clear
	g++-13 ./src/*.cpp -o ./out/main $(CFLAGS) $(LFLAGS)
	./out/main
