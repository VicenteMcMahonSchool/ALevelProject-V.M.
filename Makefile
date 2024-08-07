COMPILER=g++
FLAGS=`sdl2-config --cflags --libs` -std=c++23 -ldl -lm -lSDL2_image -lSDL2_ttf
SRC_DIR=./src
OBJ_DIR=./obj
SRCS=$(shell find ${SRC_DIR} -name *.cpp -not -type d | xargs echo)
OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
HEADERS=$(shell find ${SRC_DIR} -name *.hpp -not -type d | xargs echo)
BIN=./out/main
DEPS=$(patsubst $(OBJ_DIR)/%.o, $(OBJ_DIR)/%.d, $(OBJS))

$(BIN): $(OBJS) $(HEADERS)
	$(COMPILER) $(OBJS) -o $@ $(FLAGS)
-include $(DEPS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(COMPILER) $(FLAGS) -MMD -c $< -o $@