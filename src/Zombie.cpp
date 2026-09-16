#include "Zombie.h"

#include "SpriteRenderer.h"

Zombie::Zombie(GameObject& associated) : Component(associated) {
    hitpoints = 100;
}
void Zombie::Damage(int damage) {
    hitpoints -= damage;

    SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();

    if (hitpoints <= 0) {
        sprite->SetFrame(5);
    }
}

void Zombie::Update(float dt) {
    Damage(1);
}

void Zombie::Render() {}