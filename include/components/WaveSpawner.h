#ifndef WAVESPAWNER_H
#define WAVESPAWNER_H

#include <vector>

#include "GameObject.h"
#include "Timer.h"
#include "Vec2.h"
#include "Wave.h"
#include "components/Component.h"

// Cria zumbis fora da tela, wave por wave. Só passa para a próxima
// wave quando não houver mais zumbis vivos. Ao fim da última, se deleta.
class WaveSpawner : public Component {
   public:
    WaveSpawner(GameObject& associated);

    void Update(float dt);
    void Render();

   private:
    int zombieCounter;  // Zumbis já criados na wave atual
    std::vector<Wave> waves;
    Timer zombieCooldownTimer;
    int currentWave;

    static Vec2 RandomSpawnPosition();
};

#endif