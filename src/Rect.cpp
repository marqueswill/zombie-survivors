#include "Rect.h"

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

Rect Rect::operator+(const Vec2& offset) const {
    return Rect(x + offset.x, y + offset.y, w, h);
}