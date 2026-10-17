#include "components/Zombie.h"

#include "Camera.h"
#include "InputManager.h"
#include "components/Animator.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated),
      hitpoints(30),
      deathSound(Sound("assets/audio/Dead.wav")),
      hit0Sound(Sound("assets/audio/Hit0.wav")) {
}

void Zombie::Damage(int damage) {
    if (dead) {
        return;
    }

    hitpoints -= damage;
    hit0Sound.Play(1);

    Animator* animator = associated.GetComponent<Animator>();

    if (hitpoints <= 0) {
        dead = true;
        hit = false;
        deathTimer.Restart();

        if (animator != nullptr) {
            animator->SetAnimation("dead");
        }

        deathSound.Play(1);
    } else {
        hit = true;
        hitTimer.Restart();

        if (animator != nullptr) {
            animator->SetAnimation("hit");
        }
    }
}

void Zombie::Update(float dt) {
    // Morto: permanece na tela por cinco segundos.
    if (dead) {
        deathTimer.Update(dt);

        if (deathTimer.Get() >= 5.0f) {
            associated.RequestDelete();
        }

        return;
    }

    // Vivo: volta a andar meio segundo após receber dano.
    if (hit) {
        hitTimer.Update(dt);

        if (hitTimer.Get() >= 0.5f) {
            hit = false;

            Animator* animator =
                associated.GetComponent<Animator>();

            if (animator != nullptr) {
                animator->SetAnimation("walking");
            }
        }
    }

    // Causa dano se clicar nele
    InputManager& input = InputManager::GetInstance();
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        Vec2 mouseWorld(
            input.GetMouseX() + Camera::pos.x,
            input.GetMouseY() + Camera::pos.y);

        if (associated.box.contains(mouseWorld)) {
            Damage(10);
        }
    }
}

void Zombie::Render() {}