#ifndef SKULLBREAKER_INPUT_H
#define SKULLBREAKER_INPUT_H

#include <windows.h>

class Input {
public:
    static void OcultarCursor(bool ocultar) {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        GetConsoleCursorInfo(out, &info);

        if (ocultar) {
            info.dwSize = 1;
            info.bVisible = FALSE;
        } else {
            info.dwSize = 25;
            info.bVisible = TRUE;
        }
        SetConsoleCursorInfo(out, &info);
    }

    static void Liberar() {
        ClipCursor(NULL);
        ShowCursor(TRUE);
    }
};

#endif //SKULLBREAKER_INPUT_H
