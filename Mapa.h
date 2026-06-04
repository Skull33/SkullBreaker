#ifndef SKULLBREAKER_MAPA_H
#define SKULLBREAKER_MAPA_H

#include <vector>
#include "Entidad.h"

class SkullBreakerGraphics;

class Mapa {
public:
    vector<vector<char>> celdas;
    vector<Entidad> entidades;

    Mapa() {
        cout << "Inicializando mapa..." << endl;
        celdas.resize(21, vector<char>(40, ' '));
        cout << "Mapa inicializado correctamente." << endl;
    }

    void SpawnEntidad(Entidad e) {
        entidades.push_back(e);
    }
    void Dibujar(SkullBreakerGraphics &ss);

    void InicializarNivel() {
        for(auto &fila : celdas) {
            fill(fila.begin(), fila.end(), ' ');
        }

        // Ahora dibujamos los bordes
        for (int j = 0; j < 40; j++) {
            celdas[0][j] = '#';
            celdas[20][j] = '#';
        }
        for (int i = 0; i < 21; i++) {
            celdas[i][0] = '#';
            celdas[i][39] = '#';
        }
        for (int j = 10; j < 20; j++) {
            celdas[10][j] = '#';
            celdas[15][j] = '#';
        }
        for (int i = 10; i < 15; i++) {
            celdas[i][10] = '#';
            celdas[i][19] = '#';
        }
    }
};

#include "Skull_breaker_graphics.h"
inline void Mapa::Dibujar(SkullBreakerGraphics &ss) {
    for (int i = 0; i < celdas.size(); i++) {
        for (int j = 0; j < celdas[i].size(); j++) {
            if (celdas[i][j] != ' ') {
                ss.dibujar(j, i, celdas[i][j], RGB(89,65,58));
            }
        }
    }

    for (auto &e : entidades) {
        ss.dibujar((int)e.x, (int)e.y, e.c, e.color);
    }
}

#endif //SKULLBREAKER_MAPA_H
