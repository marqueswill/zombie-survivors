#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <memory>

#include "GameObject.h"
#include "Vec2.h"

class GameObjectFactory {
   public:
    static GameObject* CreateBackground();
    static GameObject* CreateTileMap(bool drawBorder = false);
    static GameObject* CreateZombie(float x, float y);
    static GameObject* CreatePlayer(float x, float y);
    static GameObject* CreateGun(std::weak_ptr<GameObject> character);
    static GameObject* CreateBullet(Vec2 position, float angle, float speed, int damage, float maxDistance);
};

#endif