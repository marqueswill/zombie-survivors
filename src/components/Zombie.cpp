#include "components/Zombie.h"

#include "Camera.h"
#include "InputManager.h"
#include "components/Animator.h"
#include "components/Bullet.h"
#include "components/Character.h"
#include "components/Collider.h"

#define ZOMBIE_SPEED 100.0f

int Zombie::zombieCount = 0;

Zombie::Zombie(GameObject& associated)
    : Component(associated),
      hitpoints(30),
      deathSound(Sound("assets/audio/Dead.wav")),
      hit0Sound(Sound("assets/audio/Hit0.wav")) {
    associated.AddComponent(new Collider(associated, {0.6f, 0.8f}));
    zombieCount++;
}

Zombie::~Zombie() {
    zombieCount--;
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

        if (hitTimer.Get() < 0.5f) {
            return;
        }

        hit = false;
    }

    // Anda em linha reta até o player, com velocidade constante
    if (Character::player == nullptr) {
        return;
    }

    Vec2 direction = Character::player->GetPosition() - associated.box.getCenter();

    if (direction.mod() > 1) {
        Vec2 step = direction.normalize() * ZOMBIE_SPEED * dt;
        associated.box.x += step.x;
        associated.box.y += step.y;
    }

    Animator* animator = associated.GetComponent<Animator>();
    if (animator != nullptr) {
        animator->SetAnimation("walking");
    }
}

void Zombie::Render() {}

// Toma dano das Bullets
void Zombie::NotifyCollision(GameObject& other) {
    Bullet* bullet = other.GetComponent<Bullet>();
    if (bullet != nullptr && !bullet->targetsPlayer) {
        Damage(bullet->GetDamage());
    }
}