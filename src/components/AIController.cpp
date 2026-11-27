#include "components/AIController.h"

#include "components/Character.h"

#define REST_COOLDOWN 1.5f      // Tempo parado entre um tiro e o próximo movimento
#define ARRIVAL_DISTANCE 10.0f  // Perto o bastante do destino para considerar que chegou

int AIController::npcCounter = 0;

AIController::AIController(GameObject& associated)
    : Component(associated), state(RESTING) {
    npcCounter++;
}

AIController::~AIController() {
    npcCounter--;
}

void AIController::Update(float dt) {
    // Sem jogador, o NPC não faz mais nada
    if (Character::player == nullptr) {
        return;
    }

    Character* character = associated.GetComponent<Character>();
    if (character == nullptr) {
        return;
    }

    if (state == RESTING) {
        restTimer.Update(dt);

        if (restTimer.Get() >= REST_COOLDOWN) {
            destination = Character::player->GetPosition();
            state = MOVING;
        }
        return;
    }

    // MOVING
    Vec2 direction = destination - character->GetPosition();

    if (direction.mod() > ARRIVAL_DISTANCE) {
        character->Issue(Character::Command(Character::Command::MOVE, direction.x, direction.y));
        return;
    }

    // Chegou: atira onde o jogador está agora e volta a descansar
    Vec2 target = Character::player->GetPosition();
    character->Issue(Character::Command(Character::Command::SHOOT, target.x, target.y));

    restTimer.Restart();
    state = RESTING;
}

void AIController::Render() {
}