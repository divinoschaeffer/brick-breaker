# Pour générer l'exécutable à la racine du projet
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

cmake_minimum_required(VERSION 3.10)
project(BrickBreaker VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(BrickBreaker src/Main.cpp
                            src/HelloWorld.cpp
                            src/Rectangle.cpp
                            src/Paddle.cpp
                            src/Brick.cpp
                            src/GameLoop.cpp
                            src/Text.cpp
                            src/SelectableText.cpp)

#[[
# Trouver le package SDL2
find_package(SDL2 REQUIRED)

# Trouver les packages SDL2_image et SDL2_ttf
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Lier les bibliothèques SDL2, SDL2_image et SDL2_ttf
target_link_libraries(BrickBreaker PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Inclure les répertoires d'en-tête de SDL2, SDL2_image et SDL2_ttf
target_include_directories(BrickBreaker PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
]]


# Définir les chemins des bibliothèques
set(SDL2_PATH /Library/Frameworks/SDL2.framework/Versions/A/SDL2)
set(SDL2_IMAGE_PATH /Library/Frameworks/SDL2_image.framework/Versions/A/SDL2_image)
set(SDL2_TTF_PATH /Library/Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf)

# Définir les chemins des en-têtes
set(SDL2_INCLUDE_PATH /Library/Frameworks/SDL2.framework/Versions/A/Headers)
set(SDL2_IMAGE_INCLUDE_PATH /Library/Frameworks/SDL2_image.framework/Versions/A/Headers)
set(SDL2_TTF_INCLUDE_PATH /Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers)

target_link_libraries(
        BrickBreaker PRIVATE
        ${SDL2_PATH}
        ${SDL2_IMAGE_PATH}
        ${SDL2_TTF_PATH}
)

target_include_directories(
        BrickBreaker PRIVATE
        ${SDL2_INCLUDE_PATH}
        ${SDL2_IMAGE_INCLUDE_PATH}
        ${SDL2_TTF_INCLUDE_PATH}
)

include_directories(${CMAKE_SOURCE_DIR}/include)