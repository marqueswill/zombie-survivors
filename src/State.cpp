#include "State.h"

#include "Camera.h"
#include "GameObjectFactory.h"
#include "InputManager.h"
#include "components/Zombie.h"

State::State() : quitRequested(false), started(false) {
    AddObject(GameObjectFactory::CreateBackground());
    AddObject(GameObjectFactory::CreateTileMap(true));

    // AddObject(GameObjectFactory::CreateZombie(400, 450));
    // AddObject(GameObjectFactory::CreateZombie(500, 450));
    // AddObject(GameObjectFactory::CreateZombie(600, 450));
    // AddObject(GameObjectFactory::CreateZombie(700, 450));

    music = Music("assets/audio/BGM.wav");

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

// Executado uma única vez, antes do primeiro frame. Carrega os assets
// e inicia todos os objetos que já estão no vetor.
void State::Start() {
    LoadAssets();

    // Loop por índice: objetos podem adicionar outros objetos no Start
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }

    started = true;
}

// Trata da atualização do estado das entidades, testes de
// colisões e a checagem relativa ao encerramento do jogo
void State::Update(float dt) {
    // Percoore o array de objetos atualizando cada um
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    // Se um objeto foi morto, eu removo ele do array
    for (size_t i = 0; i < objectArray.size();) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        } else {
            i++;
        };
    }

    // Flag de interrupção
    InputManager& input = InputManager::GetInstance();
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
        return;
    }

    Camera::Update(dt);

    if (input.KeyPress(SPACE_KEY)) {
        // Criar Zombie na posição atual do mouse
        float mouseWorldX = input.GetMouseX() + Camera::pos.x;
        float mouseWorldY = input.GetMouseY() + Camera::pos.y;
        AddObject(GameObjectFactory::CreateZombie(mouseWorldX, mouseWorldY));
    }
}

// Trata a renderização do estado do jogo.
// Isso inclui entidades, cenários, HUD, entre outros.
void State::Render() {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

// Adiciona o objeto ao vetor e retorna um weak_ptr para ele.
// Se o State já foi iniciado, inicia o objeto imediatamente.
std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> ptr(go);
    objectArray.push_back(ptr);

    if (started) {
        go->Start();
    }

    return std::weak_ptr<GameObject>(ptr);
}

// Procura no vetor o shared_ptr que guarda o endereço go e retorna um
// weak_ptr para ele. Retorna um weak_ptr vazio se não encontrar.
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i].get() == go) {
            return std::weak_ptr<GameObject>(objectArray[i]);
        }
    }

    return std::weak_ptr<GameObject>();
}