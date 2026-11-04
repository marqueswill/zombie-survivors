#include "components/PlayerController.h"

#include "Camera.h"
#include "InputManager.h"
#include "components/Character.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {
}

void PlayerController::Start() {
}

void PlayerController::Update(float dt) {
    (void)dt;

    Character* character = associated.GetComponent<Character>();
    if (character == nullptr) {
        return;
    }

    InputManager& input = InputManager::GetInstance();

    // Movimento: soma as teclas pressionadas em um vetor de direção
    Vec2 direction(0, 0);
    if (input.IsKeyDown(W_KEY)) {
        direction.y -= 1;
    }
    if (input.IsKeyDown(S_KEY)) {
        direction.y += 1;
    }
    if (input.IsKeyDown(A_KEY)) {
        direction.x -= 1;
    }
    if (input.IsKeyDown(D_KEY)) {
        direction.x += 1;
    }

    if (direction.mod() > 0) {
        character->Issue(Character::Command(Character::Command::MOVE, direction.x, direction.y));
    }

    // Tiro: alvo é a posição do mouse no mundo (tela + câmera)
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        float targetX = input.GetMouseX() + Camera::pos.x;
        float targetY = input.GetMouseY() + Camera::pos.y;
        character->Issue(Character::Command(Character::Command::SHOOT, targetX, targetY));
    }
}

void PlayerController::Render() {
}