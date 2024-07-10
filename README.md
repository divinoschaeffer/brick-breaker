# Breakout in C++ with SDL2

## Description

This project is a classic implementation of the Breakout game using C++ and the SDL2 library. The goal of the game is to destroy all the bricks on the screen by bouncing a ball with a paddle controlled by the player.

## Features

- Paddle control using keyboard keys.
- Collision management between the ball, paddle, and bricks.
- Score counting and display.
- Sounds for collisions and game events.
- Different difficulty levels.

## Requirements

To compile and run this project, you need to have the following installed on your system:

- [SDL2](https://www.libsdl.org/download-2.0.php)
- A compatible C++ compiler (GCC, Clang, MSVC, etc.)

## Installation

1. Clone the project repository:

    ```sh
    git clone https://github.com/divinoschaeffer/brick-breaker.git
    cd brick-breaker
    ```

2. Ensure SDL2 is installed on your system. For example, on Ubuntu, you can install SDL2 with the following command:

    ```sh
    sudo apt-get install libsdl2-dev
    ```

3. Compile the project:

    ```sh
    make
    ```

## Usage

To run the game, use the following command:

```sh
./BrickBreaker
