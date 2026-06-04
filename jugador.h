#ifndef SKULLBREAKER_JUGADOR_H
#define SKULLBREAKER_JUGADOR_H

#include <windows.h>
#include <cmath>
#include <math.h>

#include "Entidad.h"
#include "Mapa.h"

class Jugador:public Entidad {
public:
    float angulo;
    float velocidad;
    Jugador(float x, float y):Entidad(x, y,'@',RGB(0,255,0)) {
        angulo = 0.0f;
        velocidad = 0.1f;
    }
    void girar(float dir) {
        float sensibilidad = 0.05f;
        angulo += dir * sensibilidad;

        if (angulo > 6.28f) angulo -= 6.28f;
        if (angulo < 0) angulo += 6.28f;
    }
    void moverse(char &tecla, Mapa &mapa) {
        float n_x = x;
        float n_y = y;

        if (tecla == 'w') {
            n_x += cos(angulo) * velocidad;
            n_y += sin(angulo) * velocidad;
        }
        else if (tecla == 'a') {
            girar(1.0f);
        }
        else if (tecla == 's') {
            n_x -= cos(angulo) * velocidad;
            n_y -= sin(angulo) * velocidad;
        }
        else if (tecla == 'd') {
            girar(-1.0f);
        }

        if (mapa.celdas[(int)n_y][(int)n_x] != '#') {
            x = n_x;
            y = n_y;
        }
    }
    void  cabeaza(SkullBreakerGraphics& ss, Mapa& mapa) {
        float miraX = x + cos(angulo) * 2.0f;
        float miraY = y + sin(angulo) * 2.0f;

        ss.dibujar((int)miraX, (int)miraY, '.', RGB(255, 255, 255));
    }
    void actualizar(Mapa &mapa) {
        // 1. Giro (independiente del movimiento)
        if (GetAsyncKeyState('A') & 0x8000) girar(-1.0f);
        if (GetAsyncKeyState('D') & 0x8000) girar(1.0f);

        // 2. Movimiento (independiente del giro)
        if (GetAsyncKeyState('W') & 0x8000) {
            float n_x = x + cos(angulo) * velocidad;
            float n_y = y + sin(angulo) * velocidad;
            if (mapa.celdas[(int)n_y][(int)n_x] != '#') { x = n_x; y = n_y; }
        }
        if (GetAsyncKeyState('S') & 0x8000) {
            float n_x = x - cos(angulo) * velocidad;
            float n_y = y - sin(angulo) * velocidad;
            if (mapa.celdas[(int)n_y][(int)n_x] != '#') { x = n_x; y = n_y; }
        }
    }

    void RenderVista(SkullBreakerGraphics& ss, Mapa &mapa) {
        float FOV = 0.66f;
        for (int i = 0; i < 80; i++) {
            float angulo_rayo = (angulo - FOV / 2.0f) + (FOV * i / 80.0f);
            float dist = 0;
            while (mapa.celdas[(int)(y + sin(angulo_rayo) * dist)][(int)(x + cos(angulo_rayo) * dist)] != '#') {
                dist += 0.05f;
            }
            int alturaPared = (int)(20.0f / dist);
        }
    }

    void RenderizarPrimeraPersona(SkullBreakerGraphics& ss, Mapa& mapa) {
        const float FOV = 1.0f; // Campo de visión en radianes
        const int numRayos = 80; // Ancho de tu consola
        const float incrementoAngulo = FOV / (float)numRayos;
        float anguloActual = angulo - (FOV / 2.0f);

        for (int i = 0; i < numRayos; i++) {
            float distancia = 0.0f;
            bool colision = false;

            // Lanzamos el rayo hasta tocar una pared
            while (!colision && distancia < 20.0f) { // 20.0f es la distancia máxima de visión
                distancia += 0.05f;
                int x_rayo = (int)(x + cos(anguloActual) * distancia);
                int y_rayo = (int)(y + sin(anguloActual) * distancia);

                if (mapa.celdas[y_rayo][x_rayo] == '#') {
                    colision = true;
                }
            }

            // --- CÁLCULO DE LA ALTURA ---
            // Corregimos el efecto "ojo de pez" (opcional pero recomendado)
            distancia *= cos(anguloActual - angulo);

            // Calculamos cuántos caracteres de altura debe tener la columna
            int alturaColumna = (int)(20.0f / distancia);
            if (alturaColumna > 20) alturaColumna = 20;

            // Dibujamos la columna en la pantalla
            int techo = (20 - alturaColumna) / 2;
            for (int y = 0; y < 20; y++) {
                if (y < techo) ss.dibujar(i, y, ' ', RGB(50,25,50)); // Techo
                else if (y > techo + alturaColumna) ss.dibujar(i, y, ' ', RGB(0,20,25)); // Suelo
                else ss.dibujar(i, y, '|', RGB(255, 255, 255)); // Pared
            }

            anguloActual += incrementoAngulo;
        }
    }
};

#endif //SKULLBREAKER_JUGADOR_H
