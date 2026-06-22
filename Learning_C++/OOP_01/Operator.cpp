#include "Operator.h"

// Constructor implementation
Vector2D::Vector2D(int x, int y) : x(x), y(y) {}

// Getter implementations
int Vector2D::getX() const { return x; }
int Vector2D::getY() const { return y; }

// Overloading '+' operator logic
Vector2D Vector2D::operator+(const Vector2D& other) const {
    // Creates and returns a temporary object holding the sum
    return Vector2D(this->x + other.x, this->y + other.y);
}

// Overloading '<<' operator logic
std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os; // Returns the stream to allow chaining (e.g., cout << v1 << v2;)
}