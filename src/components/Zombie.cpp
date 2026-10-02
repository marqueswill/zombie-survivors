#include "components/Zombie.h"

#include <Sound.h>

#include "components/Animator.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated),
      hitpoints(100),
      deathSound(Sound("assets/audio/Dead.wav")),
      hit0Sound(Sound("assets/audio/Hit0.wav")) {
}

void Zombie::Damage(int damage) {
    if (dead) {
        return;
    }

    hitpoints -= damage;
    hit0Sound.Play(1);

    if (hitpoints <= 0) {
        dead = true;

        Animator* anim = associated.GetComponent<Animator>();
        if (anim != nullptr) {
            anim->SetAnimation("dead");
        }

        deathSound.Play(1);
    }
}

void Zombie::Update(float dt) {
    Damage(10);
}

void Zombie::Render() {}