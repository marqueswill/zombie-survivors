#include "components/Bullet.h"

#include <cmath>

#include "components/SpriteRenderer.h"
// angle em radianos
Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated),
      speed(Vec2(speed, 0).rotate(angle)),  // Velocidade é constante: calcula uma vez só
      distanceLeft(maxDistance),
      damage(damage) {
    SpriteRenderer* renderer = new SpriteRenderer(associated, "assets/img/Bullet.png");
    renderer->SetScale(0.6f, 0.6f);
    associated.AddComponent(renderer);

    // Bullet.png aponta para cima, por isso soma 90 graus
    associated.angleDeg = angle * 180 / M_PI + 90;
}

void Bullet::Update(float dt) {
    Vec2 step = speed * dt;

    associated.box.x += step.x;
    associated.box.y += step.y;

    distanceLeft -= step.mod();
    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {
}

int Bullet::GetDamage() {
    return damage;
}