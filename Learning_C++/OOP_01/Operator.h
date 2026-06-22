#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D {
private:
    int x;
    int y;

public:
    // Constructor with default arguments
    Vector2D(int x = 0, int y = 0);

    // Getters to access private data safely
    int getX() const;
    int getY() const;

    // Overloading the '+' operator (Member function)
    Vector2D operator+(const Vector2D& other) const;

    // Overloading the '<<' operator for std::cout (Friend function)
    // It must be a friend function because the left operand is std::ostream, not Vector2D
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
};

#endif // VECTOR2D_H#pragma once
