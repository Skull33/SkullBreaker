
#ifndef SKULLBREAKER_SKULL_BREAKER_GRAPHICS_H
#define SKULLBREAKER_SKULL_BREAKER_GRAPHICS_H

#include <vector>
#include <windows.h>
#include <iostream>

using namespace std;

class SkullBreakerGraphics {
public:
    SkullBreakerGraphics():ancho(0), alto(0) {
        consoleWindow = GetConsoleWindow();
        hdc = GetDC(consoleWindow);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            ancho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            alto = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);
        redimensionar();
    }
    ~SkullBreakerGraphics() {
        if (hdc != nullptr) {
            ReleaseDC(consoleWindow, hdc);
        }
    }
    void dibujar(int x, int y, char c, COLORREF color = RGB(255, 255, 255)) {
        if (x >= 0 && x < ancho && y >= 0 && y < alto) {
            buffer[y][x] = c;
            bufferColores[y][x] = color;
        }
    }
    void SetEscala(int n_escala) {
        if (n_escala > 0) {
            escala = n_escala;
        }
    }
    int GetEscala() {
        return escala;
    }
    void limpiar() {
        COORD cursorPosition;
        cursorPosition.X = 0;
        cursorPosition.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                buffer[i][j] = ' ';
                bufferColores[i][j] = RGB(0, 0, 0);
            }
        }
    }
    void Limpiarpantalla() {
        system("cls");
    }
    void renderizar() {
        HDC hdcmem = CreateCompatibleDC(hdc);
        HBITMAP hbmem = CreateCompatibleBitmap(hdc,ancho * escala,alto * escala);
        HGDIOBJ hOldBitmap = SelectObject(hdcmem, hbmem);

        COORD coord = {0,0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        /*RECT rect = {0,0,ancho * escala,alto * escala};
        FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));*/

        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                if(buffer[i][j] != ' ') {
                    RECT cell = {j * escala,i * escala,(j + 1) * escala,(i + 1) * escala};
                    HBRUSH brush = CreateSolidBrush(bufferColores[i][j]);
                    FillRect(hdcmem, &cell, brush);
                    DeleteObject(brush);
                }
            }
        }

        BitBlt(hdc, 0, 0, ancho * escala, alto * escala, hdcmem, 0, 0, SRCCOPY);
        SelectObject(hdcmem, hOldBitmap);
        DeleteObject(hbmem);
        DeleteDC(hdcmem);
    }

private:
    int alto, ancho;
    int escala = 10;
    vector<vector<char>>buffer;
    vector<vector<COLORREF>>bufferColores;
    HWND consoleWindow;
    HDC hdc;
    void redimensionar() {
        if (alto <= 0 || ancho <= 0) {
            // Fallback de seguridad: valores mínimos para que no explote
            alto = 20;
            ancho = 40;
        }

        buffer.clear(); // Limpia antes de redimensionar
        bufferColores.clear();

        buffer.resize(alto, vector<char>(ancho, ' '));
        bufferColores.resize(alto, vector<COLORREF>(ancho, RGB(0, 0, 0)));
    }
};
#endif //SKULLBREAKER_SKULL_BREAKER_GRAPHICS_H
