#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "GameObject.h"
#include "Timer.h"
#include "Vec2.h"
#include "components/Component.h"

// Controla um Character não jogável com uma máquina de estados:
// RESTING espera o cooldown; MOVING anda até o jogador e, ao chegar, atira nele.
class AIController : public Component {
   public:
    AIController(GameObject& associated);

    void Update(float dt);
    void Render();

   private:
    enum AIState { MOVING,
                   RESTING };

    int npcCounter;
    AIState state;
    Timer restTimer;
    Vec2 destination;
};

#endif