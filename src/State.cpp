#include "State.h"

#include "components/Animator.h"
#include "components/SpriteRenderer.h"
#include "components/Zombie.h"

State::State() {
    GameObject* bgObject = new GameObject();
    SpriteRenderer* bgSprite = new SpriteRenderer(*bgObject, "assets/img/Background.png");
    bgObject->AddComponent(bgSprite);
    AddObject(bgObject);

    GameObject* enemyObject = new GameObject();

    Zombie* zombie = new Zombie(*enemyObject);
    enemyObject->AddComponent(zombie);

    Animator* zombieAnimations = new Animator(*enemyObject);

    zombieAnimations->AddAnimation("walking", Animation(0, 3, 10));
    zombieAnimations->AddAnimation("dead", Animation(5, 5, 0));
    enemyObject->AddComponent(zombieAnimations);

    SpriteRenderer* enemySprite = new SpriteRenderer(*enemyObject, "assets/img/Enemy.png", 3, 2);
    // enemySprite->SetFrame(1);
    enemyObject->box.x = 600;
    enemyObject->box.y = 450;
    enemyObject->AddComponent(enemySprite);

    zombieAnimations->SetAnimation("walking");

    AddObject(enemyObject);

    music = Music("assets/audio/BGM.wav");
    quitRequested = false;
    // music.Play(-1);
}

State::~State() {
    objectArray.clear();
}

// Retorna o valor da flag de mesmo nome na função, que
// será usado por Game para interromper o game loop.
bool State::QuitRequested() {
    return quitRequested;
}

// Método que cuida de pré-carregar os assets do state do jogo para que não
// haja problemas futuros como, por exemplo, o jogo tentar tocar a música antes dela terminar de ser carregada para a
// memória.
//
// Deixe para carregar imagens/fontes/músicas às suas variáveis
// aqui sempre que for possível
void State::LoadAssets() {
}

// Trata da atualização do estado das entidades, testes de
// colisões e a checagem relativa ao encerramento do jogo
void State::Update(float dt) {
    // Percoore o array de objetos atualizando cada um
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    // Flag de interrupção
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }

    // Se um objeto foi morto, eu removo ele do array
    for (size_t i = 0; i < objectArray.size();) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        } else {
            i++;
        };
    }
}

// Trata a renderização do estado do jogo.
// Isso inclui entidades, cenários, HUD, entre outros.
void State::Render() {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}
