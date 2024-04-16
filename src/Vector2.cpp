//
// Created by Bryan on 15/04/2024.
//

#include "Vector2.h"

void Vector2::Test() {
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(3.0f, 4.0f);

    Vector2 sum = v1 + v2;
    Vector2 minus = v1 - v2;
    float dotProduct = v1 * v2;

    std::cout << "Sum: (" << sum.x << ", " << sum.y << ")\n";
    std::cout << "Minus: (" << minus.x << ", " << minus.y << ")\n";
    std::cout << "Dot product: " << dotProduct << "\n";

    // Vérifiez les résultats
    if (sum.x == 4.0f && sum.y == 6.0f) {
        std::cout << "Sum test passed.\n";
    } else {
        std::cout << "Sum test failed.\n";
    }

    if (minus.x == -2.0f && minus.y == -2.0f) {
        std::cout << "Minus test passed.\n";
    } else {
        std::cout << "Minus test failed.\n";
    }

    if (dotProduct == 11.0f) {
        std::cout << "Dot product test passed.\n";
    } else {
        std::cout << "Dot product test failed.\n";
    }
}
