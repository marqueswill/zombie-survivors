#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "GameObject.h"
#include "Sound.h"
#include "components/Component.h"

class Zombie : public Component {
   public:
    Zombie(GameObject& associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();

   private:
    int hitpoints;
    Sound deathSound;
    Sound hit0Sound;
    bool dead = false;
};

#endif