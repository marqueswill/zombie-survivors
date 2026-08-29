#ifndef STATE_H
#define STATE_H

#define INCLUDE_SDL
#include "Music.h"
#include "SDL_include.h"
#include "Sprite.h"

// State é um "estado da tela de jogo". Podemos ter uma tela de
// apresentação, uma tela de NewGame, a tela do jogo em si, uma tela
// de fim de jogo, etc. Cada um desses seria um State.
class State {
   public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

   private:
    Sprite bg;
    Music music;
    bool quitRequested;
};

#endif