#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>

#define INCLUDE_SDL
#include "SDL_include.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

class InputManager {
   public:
    static InputManager& GetInstance();

    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

   private:
    InputManager();
    ~InputManager();

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    bool mouseState[6];  // registra se o botão do mouse está ou não sendo pressionado
    int mouseUpdate[6];  // registra o último frame em que o estado do botao do mouse foi alterado

    std::unordered_map<int, bool> keyState;  // registra se a tecla está ou não sendo pressionada
    std::unordered_map<int, int> keyUpdate;  // registra o último frame em que a tecla específica foi alterada

    bool quitRequested;
    int updateCounter;  // frame de referência atual

    int mouseX;
    int mouseY;
};

#endif