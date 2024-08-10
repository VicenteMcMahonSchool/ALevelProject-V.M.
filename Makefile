COMPILER=g++
FLAGS=`sdl2-config --cflags --libs` -std=c++23 -ldl -lm -lSDL2_image -lSDL2_ttf
SRC_DIR=./src
HEADERS=$(shell find ${SRC_DIR} -name *.hpp -not -type d | xargs echo)

SRC_GAME_DIR=${SRC_DIR}/game
OBJ_GAME_DIR=./obj/game
SRCS_GAME=$(shell find ${SRC_GAME_DIR} -name *.cpp -not -type d | xargs echo)
OBJS_GAME=$(patsubst $(SRC_GAME_DIR)/%.cpp, $(OBJ_GAME_DIR)/%.o, $(SRCS_GAME))
DEPS_GAME=$(patsubst $(OBJ_GAME_DIR)/%.o, $(OBJ_GAME_DIR)/%.d, $(OBJS_GAME))
BIN_GAME=./out/main

SRC_MAKE_MAP_DIR=${SRC_DIR}/make_map
OBJ_MAKE_MAP_DIR=./obj/make_map
SRCS_MAKE_MAP=$(shell find ${SRC_MAKE_MAP_DIR} -name *.cpp -not -type d | xargs echo)
OBJS_MAKE_MAP=$(patsubst $(SRC_MAKE_MAP_DIR)/%.cpp, $(OBJ_MAKE_MAP_DIR)/%.o, $(SRCS_MAKE_MAP))
BIN_MAKE_MAP=./out/make_map
DEPS_MAKE_MAP=$(patsubst $(OBJ_MAKE_MAP_DIR)/%.o, $(OBJ_MAKE_MAP_DIR)/%.d, $(OBJS_MAKE_MAP))

all: $(BIN_GAME) $(BIN_MAKE_MAP)

$(BIN_GAME): $(OBJS_GAME) $(HEADERS)
	$(COMPILER) $(OBJS_GAME) -o $@ $(FLAGS)
$(BIN_MAKE_MAP): $(OBJS_MAKE_MAP) $(HEADERS)
	$(COMPILER) $(OBJS_MAKE_MAP) -o $@ $(FLAGS)
-include $(DEPS_GAME)
-include $(DEPS_MAKE_MAP)
$(OBJ_GAME_DIR)/%.o: $(SRC_GAME_DIR)/%.cpp
	mkdir -p $(@D)
	$(COMPILER) $(FLAGS) -MMD -c $< -o $@
$(OBJ_MAKE_MAP_DIR)/%.o: $(SRC_MAKE_MAP_DIR)/%.cpp
	mkdir -p $(@D)
	$(COMPILER) $(FLAGS) -MMD -c $< -o $@