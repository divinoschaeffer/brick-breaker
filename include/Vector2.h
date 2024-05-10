//
// Created by Bryan on 15/04/2024.
//

#ifndef VECTOR2_H
#define VECTOR2_H
#include <iostream>

class Vector2 {
public:
    float x;
    float y;

    Vector2(float x = 0, float y = 0) : x(x), y(y) {}

    // Surcharge de l'opérateur +
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // Surcharge de l'opérateur -
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // Surcharge de l'opérateur *
    float operator*(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    // Multiplication par un scalaire
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // Division par un scalaire
    Vector2 operator/(float scalar) const {
        if (scalar != 0) {
            return Vector2(x / scalar, y / scalar);
        } else {
            std::cerr << "Error: Division by zero is not allowed." << std::endl;
            return Vector2();
        }
    }

    float norm() const {
        return std::sqrt(x * x + y * y);
    }

    static void Test();
};

#endif //VECTOR2_H
