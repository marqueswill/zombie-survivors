#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Vec2.h"
#include "components/Component.h"

// Projétil genérico: anda em linha reta com velocidade constante
// até percorrer maxDistance, e então se remove.
class Bullet : public Component {
   public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance);

    void Update(float dt);
    void Render();
    int GetDamage();

   private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif