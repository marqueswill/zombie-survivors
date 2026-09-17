#include "components/Zombie.h"

// #include "components/SpriteRenderer.h"
// class SpriteRenderer;
// class Animator;
#include "components/Animator.h"

Zombie::Zombie(GameObject& associated) : Component(associated) {
    hitpoints = 100;
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;

    // SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();
    Animator* anim = associated.GetComponent<Animator>();

    if (hitpoints <= 0) {
        // sprite->SetFrame(5);
        anim->SetAnimation("dead");
    }
}

void Zombie::Update(float dt) {
    Damage(1);
}

void Zombie::Render() {}