#include "State.h"

#include "SpriteRenderer.h"

State::State() {
    GameObject* bgObject = new GameObject();
    SpriteRenderer* bgSprite = new SpriteRenderer(*bgObject, "img/ocean.png");
    bgObject->AddComponent(bgSprite);
    AddObject(bgObject);

    music = Music("assets/audio/BGM.wav");
    quitRequested = false;
    music.Play(-1);
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
    for (auto& obj : objectArray) {
        obj->Update(dt);
    }

    if (SDL_QuitRequested()) {
        quitRequested = true;
    }

    for (int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(std::remove(objectArray.begin(), objectArray.end(), objectArray[i]), objectArray.end());
        };
    }
}

// Trata a renderização do estado do jogo.
// Isso inclui entidades, cenários, HUD, entre outros.
void State::Render() {
    bg.Render(0, 0);

    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(0);
    }
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}
