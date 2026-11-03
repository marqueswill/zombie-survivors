#include "components/Character.h"

#include "Game.h"
#include "components/Animator.h"
#include "components/Gun.h"
#include "components/SpriteRenderer.h"
Character* Character::player = nullptr;

Character::Command::Command(CommandType type, float x, float y)
    : type(type), pos(x, y) {
}

Character::Character(GameObject& associated, std::string sprite)
    : Component(associated),
      speed(0, 0),
      linearSpeed(200),
      hp(100) {
    // Player.png: 3 colunas x 4 linhas
    associated.AddComponent(new SpriteRenderer(associated, sprite, 3, 4));

    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 5, 0.1f));
    animator->AddAnimation("idle", Animation(6, 9, 0.2f));
    animator->AddAnimation("dead", Animation(10, 11, 0.5f));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);

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

    GameObject* gunObject = new GameObject();
    gunObject->AddComponent(new Gun(*gunObject, state.GetObjectPtr(&associated)));

    gun = state.AddObject(gunObject);
}

void Character::Update(float dt) {
    Animator* animator = associated.GetComponent<Animator>();

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

    if (animator != nullptr) {
        if (speed.mod() > 0) {
            animator->SetAnimation("walking");
        } else {
            animator->SetAnimation("idle");
        }
    }
}

void Character::Render() {
}

// Coloca a tarefa na fila
void Character::Issue(Command task) {
    taskQueue.push(task);
}