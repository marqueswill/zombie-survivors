#include "GameObjectFactory.h"

#include "components/Animator.h"
#include "components/Bullet.h"
#include "components/Character.h"
#include "components/Gun.h"
#include "components/PlayerController.h"
#include "components/SpriteRenderer.h"
#include "components/TileMap.h"
#include "components/TileSet.h"
#include "components/Zombie.h"

GameObject* GameObjectFactory::CreateBackground() {
    GameObject* object = new GameObject();

    object->box.x = 0;
    object->box.y = 0;

    SpriteRenderer* renderer = new SpriteRenderer(*object, "assets/img/Background.png");

    // cameraFollower true para o background permanecer fixo na tela
    renderer->SetCameraFollower(true);
    object->AddComponent(renderer);

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

    animator->AddAnimation(
        "hit",
        Animation(4, 4, 0));

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

// Cria o personagem do jogador centralizado em (x, y)
GameObject* GameObjectFactory::CreatePlayer(float x, float y) {
    GameObject* object = new GameObject();

    // Character adiciona o SpriteRenderer, que define box.w e box.h
    object->AddComponent(new Character(*object, "assets/img/Player.png"));

    object->box.x = x - object->box.w / 2;
    object->box.y = y - object->box.h / 2;

    object->AddComponent(new PlayerController(*object));

    return object;
}

// Cria a arma que acompanha o personagem indicado
GameObject* GameObjectFactory::CreateGun(std::weak_ptr<GameObject> character) {
    GameObject* object = new GameObject();

    object->AddComponent(new Gun(*object, character));

    return object;
}

// Cria um projétil centralizado em position, indo na direção de angle (radianos)
GameObject* GameObjectFactory::CreateBullet(Vec2 position, float angle, float speed, int damage, float maxDistance) {
    GameObject* object = new GameObject();

    // Bullet adiciona o SpriteRenderer, que define box.w e box.h
    object->AddComponent(new Bullet(*object, angle, speed, damage, maxDistance));

    object->box.x = position.x - object->box.w / 2;
    object->box.y = position.y - object->box.h / 2;

    return object;
}