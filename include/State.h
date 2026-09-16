#ifndef STATE_H
#define STATE_H

#define INCLUDE_SDL
#include <vector>

#include "GameObject.h"
#include "Music.h"
#include "SDL_include.h"
#include "Sprite.h"

// State é um "estado da tela de jogo". Podemos ter uma tela de
// apresentação, uma tela de NewGame, a tela do jogo em si, uma tela
// de fim de jogo, etc. Cada um desses seria um State.
class State {
   public:
    State();
    ~State();

    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void AddObject(GameObject* go);

   private:
    // Sprite bg;
    std::vector<std::unique_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested;
};

#endif