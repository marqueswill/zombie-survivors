#ifndef GUN_H
#define GUN_H

#include <memory>

#include "GameObject.h"
#include "Sound.h"
#include "Timer.h"
#include "Vec2.h"
#include "components/Component.h"

// Arma que acompanha um Character. Fica ao redor do corpo, apontando
// para onde foi o último tiro, e simula o ciclo de uma pump action.
class Gun : public Component {
   public:
    Gun(GameObject& associated, std::weak_ptr<GameObject> character);

    void Update(float dt);
    void Render();
    void Shoot(Vec2 target);

   private:
    Sound shotSound;
    Sound reloadSound;
    int cooldownState;  // 0 pronta, 1 pós-tiro, 2 recarregando, 3 recarregada
    Timer cdTimer;
    std::weak_ptr<GameObject> character;
    float angle;  // Radianos
};

#endif