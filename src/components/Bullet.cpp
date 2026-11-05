#include "components/Bullet.h"

#include "components/SpriteRenderer.h"

// angle em radianos
Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated),
      speed(Vec2(speed, 0).rotate(angle)),  // Velocidade é constante: calcula uma vez só
      distanceLeft(maxDistance),
      damage(damage) {
    associated.AddComponent(new SpriteRenderer(associated, "assets/img/Bullet.png"));
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