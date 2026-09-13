#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <algorithm>
#include <memory>
#include <vector>

#include "Component.h"
#include "Rect.h"
// GameObject é um agrupador de lógicas que estarão implementadas em
// seus componentes. Todo GameObject (GO) possui uma posição no jogo (box).
class GameObject {
   public:
    GameObject();
    ~GameObject();

    Rect box;

    bool IsDead();

    void Update(float dt);
    void Render();
    void RequestDelete();

    template <typename T>
    T* GetComponent();

    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);

   private:
    std::vector<Component*> components;
    bool isDead;
};

// Retorna um ponteiro para o componente do tipo solicitado que estiver
// adicionado nesse objeto.
template <typename T>
T* GameObject::GetComponent() {
    long unsigned int index;
    for (index = 0; index < components.size(); index++) {
        T* component = dynamic_cast<T*>(components[index].get());
        if (component != nullptr) {
            return component;
        }
    }
    return nullptr;
}

#endif
