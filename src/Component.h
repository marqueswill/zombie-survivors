#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

// Essa é a classe que deve ser utilizada para adicionar lógica ao jogo
// utilizando herança. Todos os componentes do nosso jogo terão, no mínimo,
// as seguintes características:
// - Referência ao GameObject que o contém.
// - Função que atualiza estado do componente.
// - Função para renderizar o que for necessário.
class Component {
   public:
    Component(GameObject& associated);
    virtual ~Component();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

   protected:
    GameObject& associated;
};

#endif
