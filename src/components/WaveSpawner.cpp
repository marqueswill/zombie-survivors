#include "components/WaveSpawner.h"

#include <cmath>
#include <cstdlib>

#include "Camera.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "components/Zombie.h"

// Distância do centro da tela onde os inimigos nascem.
// A janela é 1200x900, então metade da diagonal é 750.
#define SPAWN_DISTANCE 800.0f

// Ponto em uma direção aleatória, longe o bastante do centro da tela
// para o inimigo não aparecer na frente do jogador
Vec2 WaveSpawner::RandomSpawnPosition() {
    Vec2 screenCenter = Camera::pos + Vec2(600, 450);
    float angle = (rand() / (float)RAND_MAX) * 2 * M_PI;

    return screenCenter + Vec2(SPAWN_DISTANCE, 0).rotate(angle);
}

WaveSpawner::WaveSpawner(GameObject& associated)
    : Component(associated), zombieCounter(0), currentWave(0) {
    waves.push_back(Wave(5, 1.5f));
    waves.push_back(Wave(8, 1.0f));
    waves.push_back(Wave(12, 0.7f));
    waves.push_back(Wave(20, 0.4f));
}

void WaveSpawner::Update(float dt) {
    zombieCooldownTimer.Update(dt);

    Wave& wave = waves[currentWave];

    if (zombieCounter < wave.zombies) {
        if (zombieCooldownTimer.Get() >= wave.cooldown) {
            Vec2 pos = RandomSpawnPosition();
            Game::GetInstance().GetState().AddObject(GameObjectFactory::CreateZombie(pos.x, pos.y));

            zombieCounter++;
            zombieCooldownTimer.Restart();
        }
        return;
    }

    // Todos os zumbis da wave já nasceram: espera não sobrar inimigo
    if (Zombie::zombieCount > 0) {
        return;
    }
    
    currentWave++;
    zombieCounter = 0;
    zombieCooldownTimer.Restart();

    if (currentWave >= (int)waves.size()) {
        associated.RequestDelete();
    }
}

void WaveSpawner::Render() {
}
