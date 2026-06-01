
#ifndef SKULLBREAKER_SKULL_BREAKER_GRAPHICS_H
#define SKULLBREAKER_SKULL_BREAKER_GRAPHICS_H

#include <vector>
#include <windows.h>
#include <iostream>

using namespace std;

class SkullBreakerGraphics {
public:
    SkullBreakerGraphics() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        ancho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        alto = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        redimensionar();
    }
    void limpiar() {
        COORD cursorpos;
        cursorpos.X = 0;
        cursorpos.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorpos);
        for (int i = 0; i < alto; i++) {
            cout<< string(buffer[i].begin(), buffer[i].end()) << endl;
        }
    }
    void Limpiarpantalla() {
        system("cls");
    }
    void dibujar(int x, int y, char c) {
        if (x >= 0 && x < ancho && y >= 0 && y < alto) {
            buffer[y][x] = c;
        }
    }
    void renderizar() {
        COORD coord = {0,0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        string pantalla = " ";
        for (int i = 0; i < alto; i++) {
            pantalla.append(buffer[i].begin(), buffer[i].end());
            pantalla += "\n";
        }

        cout<<pantalla;
    }
private:
    int alto, ancho;
    vector<vector<char>>buffer;
    void redimensionar() {
        buffer.resize(alto);
        for (int i = 0; i < alto; i++) {
            buffer[i].resize(ancho, ' ');
        }
    };
};
#endif //SKULLBREAKER_SKULL_BREAKER_GRAPHICS_H
