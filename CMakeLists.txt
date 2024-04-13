cmake_minimum_required(VERSION 3.10)
project(BrickBreaker VERSION 1.0.0)

add_executable(BrickBreaker Main.cpp)

# On ajoute les librairies SDL2, SDL2_image et SDL2_ttf
target_link_libraries(
        BrickBreaker PRIVATE
        /Library/Frameworks/SDL2.framework/Versions/A/SDL2
        /Library/Frameworks/SDL2_image.framework/Versions/A/SDL2_image
        /Library/Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
)

target_include_directories(
        BrickBreaker PRIVATE
        /Library/Frameworks/SDL2.framework/Versions/A/Headers
        /Library/Frameworks/SDL2_image.framework/Versions/A/Headers
        /Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers
)
