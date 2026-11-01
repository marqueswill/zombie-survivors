#ifndef STATE_H
#define STATE_H

#define INCLUDE_SDL
#include <memory>
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
    void Start();
    void Update(float dt);
    void Render();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

   private:
    // Sprite bg;
    std::vector<std::shared_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested;
    bool started;
};

#endif