#ifndef SKULLBREAKER_SKULL_BREAKER_KERNEL_H
#define SKULLBREAKER_SKULL_BREAKER_KERNEL_H

#include "Skull_breaker_graphics.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Mapa.h"
#include "jugador.h"
#include "Input.h"

using namespace std;

class SkullBreakerKernel {
public:
    Mapa mapa;
    Jugador* jugador = nullptr;
    SkullBreakerKernel(){
    }
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
        cout << "Entrando al bucle de juego..." << endl;
        mapa.InicializarNivel();
        jugador = new Jugador(10,5);
        Input::OcultarCursor(true);
        bool jugando = 1;
        while (jugando) {
            ss.limpiar();
            //mapa.Dibujar(ss);
            //ss.dibujar((int)jugador->x,(int)jugador->y,jugador->c,jugador->color);
            //jugador->cabeaza(ss, mapa);
            jugador->RenderizarPrimeraPersona(ss,mapa);
            ss.renderizar();
            Sleep(8);
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                Input::OcultarCursor(false);
                Input::Liberar();
                jugando = false;
            }
            jugador->actualizar(mapa);
            jugador->RenderVista(ss,mapa);
        }
        ss.Limpiarpantalla();
    }
};

#endif //SKULLBREAKER_SKULL_BREAKER_KERNEL_H
