#include "components/Gun.h"

#include <cmath>

#include "Game.h"
#include "GameObjectFactory.h"
#include "components/Animator.h"
#include "components/Bullet.h"
#include "components/SpriteRenderer.h"
// Distância entre o centro do corpo e o centro da arma
#define GUN_DISTANCE 30.0f

// Tempo (em segundos) em cada estado do cooldown
#define SHOT_DELAY 0.25f   // 1 -> 2: parada depois do tiro
#define RELOAD_TIME 0.5f   // 2 -> 3: animação de recarregar
#define READY_DELAY 0.15f  // 3 -> 0: recarregada, mas ainda não pronta

// Parâmetros do projétil
#define BULLET_SPEED 800.0f
#define BULLET_DAMAGE 10
#define BULLET_MAX_DISTANCE 1000.0f

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
    : Component(associated),
      shotSound("assets/audio/Range.wav"),
      reloadSound("assets/audio/PumpAction.mp3"),
      cooldownState(0),
      character(character),
      angle(0) {
    // Gun.png: 3 colunas x 2 linhas
    associated.AddComponent(new SpriteRenderer(associated, "assets/img/Gun.png", 3, 2));

    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(0, 0, 0));
    animator->AddAnimation("reloading", Animation(0, 5, RELOAD_TIME / 6));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);
}

void Gun::Update(float dt) {
    // Se o personagem foi deletado, a arma também deixa de existir
    std::shared_ptr<GameObject> owner = character.lock();
    if (owner == nullptr) {
        associated.RequestDelete();
        return;
    }

    // Centraliza a arma no corpo e afasta na direção do ângulo
    Vec2 center = owner->box.getCenter();
    Vec2 offset = Vec2(GUN_DISTANCE, 0).rotate(angle);

    associated.box.x = center.x + offset.x - associated.box.w / 2;
    associated.box.y = center.y + offset.y - associated.box.h / 2;

    // Rotaciona a arma para o ângulo. Se ela apontar para a esquerda,
    // espelha na vertical para não ficar de cabeça pra baixo.
    associated.angleDeg = angle * 180 / M_PI;

    SpriteRenderer* renderer = associated.GetComponent<SpriteRenderer>();
    if (renderer != nullptr) {
        renderer->SetFlip(std::cos(angle) < 0 ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    }

    // Máquina de estados do cooldown
    if (cooldownState == 0) {
        return;
    }

    cdTimer.Update(dt);
    Animator* animator = associated.GetComponent<Animator>();

    if (cooldownState == 1 && cdTimer.Get() >= SHOT_DELAY) {
        cooldownState = 2;
        cdTimer.Restart();
        reloadSound.Play(1);

        if (animator != nullptr) {
            animator->SetAnimation("reloading");
        }
    } else if (cooldownState == 2 && cdTimer.Get() >= RELOAD_TIME) {
        cooldownState = 3;
        cdTimer.Restart();

        if (animator != nullptr) {
            animator->SetAnimation("idle");
        }
    } else if (cooldownState == 3 && cdTimer.Get() >= READY_DELAY) {
        cooldownState = 0;
    }
}

void Gun::Render() {
}

void Gun::Shoot(Vec2 target) {
    if (cooldownState != 0) {
        return;
    }

    std::shared_ptr<GameObject> owner = character.lock();
    if (owner == nullptr) {
        return;
    }

    // Ângulo do centro do personagem até o alvo
    angle = (target - owner->box.getCenter()).inclination();

    // Cria o projétil saindo do cano (ponta da arma na direção do ângulo)
    Vec2 center = owner->box.getCenter();
    Vec2 muzzle = center + Vec2(GUN_DISTANCE + associated.box.w / 2, 0).rotate(angle);

    Game::GetInstance().GetState().AddObject(GameObjectFactory::CreateBullet(muzzle, angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAX_DISTANCE));

    shotSound.Play(1);
    cooldownState = 1;
    cdTimer.Restart();
}