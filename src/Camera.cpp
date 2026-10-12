#include "Camera.h"

#include "GameObject.h"
#include <InputManager.h>

Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    speed = Vec2(0, 0);

    if (focus != nullptr) {
        // Dimensões da janela criada em Game.
        constexpr float screenWidth = 1200.0f;
        constexpr float screenHeight = 900.0f;

        float centerX = focus->box.x + focus->box.w / 2.0f;
        float centerY = focus->box.y + focus->box.h / 2.0f;

        pos.x = centerX - screenWidth / 2.0f;
        pos.y = centerY - screenHeight / 2.0f;
        return;
    }

    InputManager& input = InputManager::GetInstance();
    constexpr float cameraSpeed = 400.0f;  // pixels por segundo

    if (input.IsKeyDown(SDLK_LEFT)) {
        speed.x -= cameraSpeed;
    }
    if (input.IsKeyDown(SDLK_RIGHT)) {
        speed.x += cameraSpeed;
    }
    if (input.IsKeyDown(SDLK_UP)) {
        speed.y -= cameraSpeed;
    }
    if (input.IsKeyDown(SDLK_DOWN)) {
        speed.y += cameraSpeed;
    }

    pos.x += speed.x * dt;
    pos.y += speed.y * dt;
}