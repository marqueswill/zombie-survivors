#include "InputManager.h"

InputManager::InputManager()
    : mouseState{},
      mouseUpdate{},
      quitRequested(false),
      updateCounter(0),
      mouseX(0),
      mouseY(0) {
}

InputManager::~InputManager() {
}

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::Update() {
    SDL_Event event;

    updateCounter++;
    quitRequested = false;

    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.repeat) {
                    break;
                }

                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;

            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button < 6) {
                    mouseState[event.button.button] = true;
                    mouseUpdate[event.button.button] = updateCounter;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button < 6) {
                    mouseState[event.button.button] = false;
                    mouseUpdate[event.button.button] = updateCounter;
                }
                break;

            case SDL_QUIT:
                quitRequested = true;
                break;
        }
    }
}

// True se a tecla está pressionada em um frame específico
bool InputManager::KeyPress(int key) {
    auto it = keyState.find(key);

    if (it == keyState.end()) {
        return false;
    }

    return keyState[key] && keyUpdate[key] == updateCounter;
}

// True se a tecla sendo solta em um frame específico
bool InputManager::KeyRelease(int key) {
    return !keyState[key] && keyUpdate[key] == updateCounter;
}

// True em todos frames que a tecla estiver pressionada
bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    if (button < 1 || button > 5) {
        return false;
    }

    return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}