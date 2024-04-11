# Makefile pour compiler le code SDL en C++

# Compilateur
CXX = clang++

# Options de compilation
CXXFLAGS =

# Inclusions et bibliothèques de la SDL

SDL_DIR = /opt/homebrew/Cellar/sdl2/2.30.2
SDL_TTF_DIR = /opt/homebrew/Cellar/sdl2_ttf/2.22.0

# Inclusions et bibliothèques de la SDL
SDL_INCLUDE = -I$(SDL_DIR)/include
SDL_LIBS = -L$(SDL_DIR)/lib -lSDL2

# Inclusions et bibliothèques de la SDL et de la SDL_ttf
INCLUDES = -I$(SDL_DIR)/include -I$(SDL_DIR)/include/SDL2 -I$(SDL_TTF_DIR)/include
LIBS = -L$(SDL_DIR)/lib -lSDL2 -L$(SDL_TTF_DIR)/lib -lSDL2_ttf

# Nom de l'exécutable
TARGET = brick_breaker

# Fichiers source
SRCS = main.cpp

# Générer le nom des fichiers objets à partir des fichiers source
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
