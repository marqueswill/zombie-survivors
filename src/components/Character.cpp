#include "components/Character.h"

#include "Camera.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "components/Animator.h"
#include "components/Bullet.h"
#include "components/Collider.h"
#include "components/Gun.h"
#include "components/SpriteRenderer.h"
#include "components/Zombie.h"

// Dano por contato com Zombie e intervalo mínimo entre dois danos
#define ZOMBIE_DAMAGE 10
#define ZOMBIE_DAMAGE_COOLDOWN 1.0f

Character* Character::player = nullptr;

Character::Command::Command(CommandType type, float x, float y)
    : type(type), pos(x, y) {
}

Character::Character(GameObject& associated, std::string sprite)
    : Component(associated),
      speed(0, 0),
      linearSpeed(200),
      hp(100),
      hitSound("assets/audio/Hit1.wav"),
      deathSound("assets/audio/Dead.wav"),
      facingLeft(false) {
    // Player.png: 3 colunas x 4 linhas
    associated.AddComponent(new SpriteRenderer(associated, sprite, 3, 4));

    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 5, 0.1f));
    animator->AddAnimation("idle", Animation(6, 9, 0.2f));
    animator->AddAnimation("dead", Animation(10, 11, 0.5f));
    animator->AddAnimation("walking_left", Animation(0, 5, 0.1f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("idle_left", Animation(6, 9, 0.2f, SDL_FLIP_HORIZONTAL));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);
    associated.AddComponent(new Collider(associated));

    if (player == nullptr) {
        player = this;
    }
}

Character::~Character() {
    // Avisa aos outros objetos que o player não existe mais
    if (player == this) {
        player = nullptr;
    }
}

// Cria a arma. Fica aqui (e não no construtor) porque a Gun precisa de
// um weak_ptr para este objeto, que só existe depois de ele estar no State.
void Character::Start() {
    State& state = Game::GetInstance().GetState();
    gun = state.AddObject(GameObjectFactory::CreateGun(state.GetObjectPtr(&associated)));
}

void Character::Update(float dt) {
    Animator* animator = associated.GetComponent<Animator>();

    damageCooldown.Update(dt);

    // Morto: espera a animação de morte e se remove
    if (hp <= 0) {
        if (animator != nullptr) {
            animator->SetAnimation("dead");
        }

        deathTimer.Update(dt);
        if (deathTimer.Get() >= 2.0f) {
            associated.RequestDelete();
        }

        // Descarta comandos pendentes
        taskQueue = std::queue<Command>();
        return;
    }

    speed = Vec2(0, 0);

    // Executa todas as ações pendentes, na ordem em que chegaram
    while (!taskQueue.empty()) {
        Command task = taskQueue.front();

        if (task.type == Command::MOVE) {
            // Normaliza para o módulo da velocidade ser sempre linearSpeed,
            // inclusive na diagonal
            speed = task.pos.normalize() * linearSpeed;
            associated.box.x += speed.x * dt;
            associated.box.y += speed.y * dt;
        } else if (task.type == Command::SHOOT) {
            std::shared_ptr<GameObject> gunObject = gun.lock();
            if (gunObject != nullptr) {
                Gun* gunComponent = gunObject->GetComponent<Gun>();
                if (gunComponent != nullptr) {
                    gunComponent->Shoot(task.pos);
                }
            }
        }

        taskQueue.pop();
    }

    // Só troca o lado quando há movimento horizontal
    if (speed.x < 0) {
        facingLeft = true;
    } else if (speed.x > 0) {
        facingLeft = false;
    }

    if (animator != nullptr) {
        std::string suffix = facingLeft ? "_left" : "";

        if (speed.mod() > 0) {
            animator->SetAnimation("walking" + suffix);
        } else {
            animator->SetAnimation("idle" + suffix);
        }
    }
}

void Character::Render() {
}

// Coloca a tarefa na fila
void Character::Issue(Command task) {
    taskQueue.push(task);
}

// Toma dano de Bullets e, com cooldown, de Zombies
void Character::NotifyCollision(GameObject& other) {
    if (hp <= 0) {
        return;
    }

    Bullet* bullet = other.GetComponent<Bullet>();
    if (bullet != nullptr) {
        TakeDamage(bullet->GetDamage());
        return;
    }

    if (other.GetComponent<Zombie>() != nullptr && damageCooldown.Get() >= ZOMBIE_DAMAGE_COOLDOWN) {
        TakeDamage(ZOMBIE_DAMAGE);
        damageCooldown.Restart();
    }
}

void Character::TakeDamage(int damage) {
    hp -= damage;

    if (hp <= 0) {
        deathSound.Play(1);

        // A câmera não pode continuar seguindo um objeto que vai ser deletado
        if (this == player) {
            Camera::Unfollow();
        }
    } else {
        hitSound.Play(1);
    }
}