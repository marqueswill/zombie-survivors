#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "GameObject.h"
#include "components/Component.h"

// Lê o teclado e o mouse e transforma em comandos para o Character
// que está no mesmo GameObject.
class PlayerController : public Component {
   public:
    PlayerController(GameObject& associated);

    void Start();
    void Update(float dt);
    void Render();
};

#endif