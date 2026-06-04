#ifndef SKULLBREAKER_ENTIDAD_H
#define SKULLBREAKER_ENTIDAD_H

#include <windows.h>

class Entidad {
public:
    float x, y;
    char c;
    COLORREF color;
    Entidad(float x, float y, char c, COLORREF color): x(x), y(y), c(c), color(color) {}
};

#endif //SKULLBREAKER_ENTIDAD_H
