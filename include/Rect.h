#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

// Rect expressa uma posição (canto superior esquerdo do retângulo) e dimensões.
class Rect {
   public:
    Rect();
    Rect(float x, float y, float w, float h);

    float x;
    float y;
    float w;
    float h;

    // Operações
    Rect add(const Rect& other) const;
    Rect sub(const Rect& other) const;
    Rect mult(float a) const;

    // Funções auxiliares

    // Obter coordenadas do centro de um retângulo
    Vec2 getCenter() const;

    // Distância entre o centro de dois Rects
    float distance(const Rect& other) const;

    // Saber se um ponto está dentro de um Rect
    bool contains(const Vec2& point) const;

    // Operadores
    Rect operator+(const Rect& r2) const;
    Rect operator-(const Rect& r2) const;
    Rect operator*(const float a) const;
    Rect& operator+=(const Rect& r2);
    Rect& operator-=(const Rect& r2);

    // Operações com vetores (w=0, h=0)
    Rect operator+(const Vec2& v2) const;
    Rect operator-(const Vec2& v2) const;
};
#endif