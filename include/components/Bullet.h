#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Vec2.h"
#include "components/Component.h"

// Projétil genérico: anda em linha reta com velocidade constante
// até percorrer maxDistance, e então se remove.
class Bullet : public Component {
   public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer);

    void Update(float dt);
    void Render();
    int GetDamage();
    void NotifyCollision(GameObject& other);

    // true: tiro de NPC, só acerta o player. false: tiro do player, acerta o resto.
    bool targetsPlayer;

   private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif