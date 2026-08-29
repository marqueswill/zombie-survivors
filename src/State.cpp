#include "State.h"

State::State() {
    quitRequested = false;
    bg = new Sprite();
    music = new Music("");
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
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

// Trata a renderização do estado do jogo.
// Isso inclui entidades, cenários, HUD, entre outros.
void State::Render() {}