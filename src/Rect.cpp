#include "Rect.h"

Rect::Rect() {
    x = 0.0;
    y = 0.0;
    w = 0.0;
    h = 0.0;
};

Rect::Rect(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect Rect::add(const Rect& other) const {
    return Rect(x + other.x, y + other.y, w + other.w, h + other.h);
}

Rect Rect::sub(const Rect& other) const {
    return Rect(x - other.x, y - other.y, w - other.w, h - other.h);
}

Rect Rect::mult(float a) const {
    return Rect(x * a, y * a, w * a, h * a);
}

Vec2 Rect::getCenter() const {
    float x_center = (x + w) / 2.0f;
    float y_center = (y + h) / 2.0f;

    return Vec2(x_center, y_center);
}

float Rect::distance(const Rect& other) const {
    return getCenter().distance(other.getCenter());
}

bool Rect::contains(const Vec2& point) const {
    return (point.x >= x && point.x <= x + w &&
            point.y >= y && point.y <= y + h);
}

Rect Rect::operator+(const Rect& r2) const {
    return add(r2);
}

Rect Rect::operator-(const Rect& r2) const {
    return sub(r2);
}

Rect Rect::operator*(const float a) const {
    return mult(a);
}

Rect& Rect::operator+=(const Rect& r2) {
    x += r2.x;
    y += r2.y;
    w += r2.w;
    h += r2.h;
    return *this;
}

Rect& Rect::operator-=(const Rect& r2) {
    x -= r2.x;
    y -= r2.y;
    w -= r2.w;
    h -= r2.h;
    return *this;
}

Rect Rect::operator+(const Vec2& v2) const {
    return add(Rect(v2.x, v2.y, 0, 0));
}

Rect Rect::operator-(const Vec2& v2) const {
    return sub(Rect(v2.x, v2.y, 0, 0));
}