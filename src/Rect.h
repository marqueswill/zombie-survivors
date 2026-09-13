#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

// Rect expressa uma posição (canto superior esquerdo do retângulo) e dimensões.
class Rect {
    Rect();
    Rect(float x, float y, float w, float h);

    float x;
    float y;
    float w;
    float h;

    // Funções auxiliares
    Vec2 getCenter() const;
    float distance(const Rect& other) const;
    bool contains(const Vec2& point) const;

    // Operadores
    Rect operator+(const Vec2& offset) const;
    Rect operator-(const Vec2& offset) const;
    Rect operator*(const Vec2& offset) const;
};
#endif