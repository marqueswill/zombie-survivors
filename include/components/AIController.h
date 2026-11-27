#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "GameObject.h"
#include "Timer.h"
#include "Vec2.h"
#include "components/Component.h"

// Controla um Character não jogável com uma máquina de estados:
// RESTING espera o cooldown; MOVING anda até onde o jogador estava e, ao chegar, atira nele.
class AIController : public Component {
   public:
    AIController(GameObject& associated);
    ~AIController();

    void Update(float dt);
    void Render();

    // Quantidade de NPCs existentes, para o WaveSpawner saber quando a wave acabou
    static int npcCounter;

   private:
    enum AIState { MOVING,
                   RESTING };

    AIState state;
    Timer restTimer;
    Vec2 destination;
};

#endif