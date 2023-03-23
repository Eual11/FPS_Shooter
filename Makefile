OBJS = test5.cpp

BUILD_NAME = e

all: $(OBJS)
	g++ -g $(OBJS)  -ISDL2/ -LSDL2/x86_64-w64-mingw32/bin/ -Wall -Wextra -Wpedantic -w   -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o build/$(BUILD_NAME)