

#define which compiler to use
CXX := g++
OUTPUT := sfmlgame
OS := $(shell uname)

ifeq ($(OS), Linux)
	CXX_FLAGS := -O3 -std=c++20 -Wno-unused-result -Wno-deprecated-declarations
	INCLUDES := -I./src -I./src/imgui
	LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lGL
endif

SRC_FILES := $(wildcard src/*.cpp src/imgui/*.cpp)
OBJ_FILES := $(SRC_FILES:.cpp=.o)

DEP_FILES := $(SRC_FILES:.cpp=.d)
-include $(DEP_FILES)

#all of these targets will be made if you just type make
all: $(OUTPUT)

#define the main executable requirements / commands
$(OUTPUT): $(OBJ_FILES) Makefile
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

.cpp.o:
	$(CXX) -MMD -MP -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES) ./bin/$(OUTPUT)

run: $(OUTPUT)
	cd bin && GDK_BACKEND=x11 ./$(OUTPUT) && cd ..
