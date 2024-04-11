# Makefile pour compiler le code SDL en C++

# Compilateur
CXX = clang++

# Options de compilation
CXXFLAGS =

# Répertoire d'installation de la SDL
SDL_DIR = /opt/homebrew/Cellar/sdl2/2.30.2/

# Inclusions et bibliothèques de la SDL
SDL_INCLUDE = -I$(SDL_DIR)/include
SDL_LIBS = -L$(SDL_DIR)/lib -lSDL2

# Nom de l'exécutable
TARGET = brick_breaker

# Fichiers source
SRCS = main.cpp

# Générer le nom des fichiers objets à partir des fichiers source
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SDL_INCLUDE) -o $@ $^ $(SDL_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL_INCLUDE) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
