#include "GameObjectFactory.h"

#include "components/Animator.h"
#include "components/SpriteRenderer.h"
#include "components/TileMap.h"
#include "components/TileSet.h"
#include "components/Zombie.h"

GameObject* GameObjectFactory::CreateBackground() {
    GameObject* object = new GameObject();

    object->box.x = 0;
    object->box.y = 0;

    object->AddComponent(new SpriteRenderer(*object, "assets/img/Background.png"));

    return object;
}

GameObject* GameObjectFactory::CreateTileMap(bool drawBorder) {
    GameObject* object = new GameObject();

    TileSet* tileSet = new TileSet(64, 64, "assets/img/Tileset.png");
    object->AddComponent(new TileMap(*object, "assets/map/map.txt", tileSet, drawBorder));

    return object;
}

GameObject* GameObjectFactory::CreateZombie(float x, float y) {
    GameObject* object = new GameObject();

    object->box.x = x;
    object->box.y = y;

    object->AddComponent(new Zombie(*object));

    Animator* animator = new Animator(*object);

    animator->AddAnimation(
        "walking",
        Animation(0, 3, 0.1f));

    animator->AddAnimation(
        "dead",
        Animation(5, 5, 0));

    animator->SetAnimation("walking");

    object->AddComponent(animator);

    object->AddComponent(
        new SpriteRenderer(
            *object,
            "assets/img/Enemy.png",
            3,
            2));

    return object;
}