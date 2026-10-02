#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <GameObject.h>

class GameObjectFactory {
   public:
    static GameObject* CreateBackground();
    static GameObject* CreateTileMap();
    static GameObject* CreateZombie(float x, float y);
};

#endif