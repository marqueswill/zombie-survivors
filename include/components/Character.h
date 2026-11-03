#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <queue>
#include <string>

#include "GameObject.h"
#include "Timer.h"
#include "Vec2.h"
#include "components/Component.h"

// Personagem do jogo. Não lê input diretamente: recebe comandos (Command)
// por Issue, que são executados no Update na ordem em que chegaram.
class Character : public Component {
   public:
    // Ação que pode ser dada ao personagem
    class Command {
       public:
        enum CommandType { MOVE,
                           SHOOT };

        Command(CommandType type, float x, float y);

        CommandType type;
        Vec2 pos;  // MOVE: direção do movimento. SHOOT: alvo no mundo.
    };

    Character(GameObject& associated, std::string sprite);
    ~Character();

    void Start();
    void Update(float dt);
    void Render();

    void Issue(Command task);

    // Ponteiro para o personagem do jogador, para os outros objetos o encontrarem
    static Character* player;

   private:
    std::weak_ptr<GameObject> gun;
    std::queue<Command> taskQueue;
    Vec2 speed;
    float linearSpeed;
    int hp;
    Timer deathTimer;
};

#endif