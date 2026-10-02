#include "State.h"

#include <GameObjectFactory.h>

#include "components/Zombie.h"

State::State() {
    AddObject(GameObjectFactory::CreateBackground());
    AddObject(GameObjectFactory::CreateTileMap(false));

    AddObject(GameObjectFactory::CreateZombie(400, 450));
    AddObject(GameObjectFactory::CreateZombie(500, 450));
    AddObject(GameObjectFactory::CreateZombie(600, 450));
    AddObject(GameObjectFactory::CreateZombie(700, 450));

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
