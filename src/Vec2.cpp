#include "Vec2.h"

#include <cmath>

// Vec2 expressa um vetor no R2, que pode tanto representar uma posição no
// espaço como uma grandeza.
Vec2::Vec2() {
    x = 0.0f;
    y = 0.0f;
}

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2 Vec2::add(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::sub(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::mult(float a) const {
    return Vec2(x * a, y * a);
}

float Vec2::mod() const {
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::normalize() const {
    float magnitude = mod();
    if (magnitude == 0.0f) {
        return Vec2(0.0f, 0.0f);
    }
    return Vec2(x / magnitude, y / magnitude);
}

float Vec2::distance(const Vec2& other) const {
    return sub(other).mod();
}

float Vec2::inclination() const {
    return std::atan2(y, x);
}

float Vec2::inclination(const Vec2& other) const {
    return sub(other).inclination();
}

Vec2 Vec2::rotate(float angle) const {
    float cos_theta = std::cos(angle);
    float sin_theta = std::sin(angle);

    float newX = x * cos_theta - y * sin_theta;
    float newY = y * cos_theta + x * sin_theta;

    return Vec2(newX, newY);
}

Vec2 Vec2::operator+(const Vec2& v2) const {
    return add(v2);
}

Vec2 Vec2::operator-(const Vec2& v2) const {
    return sub(v2);
}

Vec2 Vec2::operator*(const float v2) const {
    return mult(v2);
}

Vec2& Vec2::operator+=(const Vec2& v2) {
    x += v2.x;
    y += v2.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& v2) {
    x -= v2.x;
    y -= v2.y;
    return *this;
}