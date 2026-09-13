#ifndef VEC2_H
#define VEC2_H

class Vec2 {
   public:
    float x;
    float y;

    // Construtores
    Vec2();
    Vec2(float x, float y);

    // Operações
    Vec2 add(const Vec2& other) const;
    Vec2 sub(const Vec2& other) const;
    Vec2 mult(float a) const;

    // Magnitude
    float mod() const;

    // Normalização
    Vec2 normalize() const;

    // Distância entre dois pontos
    float distance(const Vec2& other) const;

    // Inclinação do vetor em relação ao eixo x (radianos)
    float inclination() const;

    // Inclinação da reta dada por dois pontos (radianos)
    float inclination(const Vec2& other) const;

    // Rotação
    Vec2 rotate(float angle) const;

    // Definição operadores
    Vec2 operator+(const Vec2& v2) const;
    Vec2 operator-(const Vec2& v2) const;
    Vec2 operator*(const float a) const;
    Vec2& operator+=(const Vec2& v2);
    Vec2& operator-=(const Vec2& v2);
};

#endif