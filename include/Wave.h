#ifndef WAVE_H
#define WAVE_H

// Configuração de uma wave: quantos zumbis nascem e o intervalo entre eles.
class Wave {
   public:
    Wave(int zombies, float cooldown);

    int zombies;
    float cooldown;
};

#endif