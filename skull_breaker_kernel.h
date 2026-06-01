#ifndef SKULLBREAKER_SKULL_BREAKER_KERNEL_H
#define SKULLBREAKER_SKULL_BREAKER_KERNEL_H

#include "Skull_breaker_graphics.h"
#include <iostream>

using namespace std;

class SkullBreakerKernel {
public:
    void ModoEditor(SkullBreakerGraphics& ss) {
        bool editando = 1;
        while (editando) {
            cout<<"Hora de editar"<<endl;
            system("pause");
            editando = 0;
            ss.Limpiarpantalla();
        }
    }
    void ModoJuego(SkullBreakerGraphics& ss) {
        bool jugando = 1;
        while (jugando) {
            ss.limpiar();
            ss.dibujar(10,5,'@');
            for (int x = 0;x < 40; x++) {
                ss.dibujar(x,0,'#');
                ss.dibujar(x,20,'#');
            }
            for (int y = 0;y < 21; y++) {
                ss.dibujar(0,y,'#');
                ss.dibujar(39,y,'#');
            }
            ss.renderizar();
            system("pause");
            jugando = 0;
            ss.Limpiarpantalla();
        }
    }
};

#endif //SKULLBREAKER_SKULL_BREAKER_KERNEL_H
