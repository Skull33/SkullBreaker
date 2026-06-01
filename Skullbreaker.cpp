#include <iostream>
#include <string>
#include "Skull_breaker_graphics.h"
#include "skull_breaker_kernel.h"

using namespace std;

int main() {
    cout<<"Bienvenido a SkullBreaker"<<endl;
    cout<<"------------------------------------------"<<endl;
    string command[] = {"salir","editar","jugar"};
    bool existe_editor = 0;
    bool existe_kernel = 0;
    SkullBreakerGraphics* ss = nullptr;
    SkullBreakerKernel * kernel = nullptr;
    while (true) {
        string comando;
        cout<<"ingrese un comando:"<<endl;
        cin>>comando;
        if (comando == "salir") {
            return 0;
        }
        else if (comando == "editar") {
            if (!existe_editor) {
                ss = new SkullBreakerGraphics();
                existe_editor = 1;
            }
            if (!existe_kernel) {
                kernel = new SkullBreakerKernel();
                existe_kernel = 1;
            }
            ss->Limpiarpantalla();
            kernel->ModoEditor(*ss);
        }
        else if (comando == "jugar") {
            if (!existe_editor) {
                ss = new SkullBreakerGraphics();
                existe_editor = 1;
            }
            if (!existe_kernel) {
                kernel = new SkullBreakerKernel();
                existe_kernel = 1;
            }
            ss->Limpiarpantalla();
            kernel->ModoJuego(*ss);
        }
        else {
            cout<<"------------------------------------------------------------"<<endl;
            cout<<"el comando "<<comando<<" no existe o no ha sido implementado"<<endl;
            cout<<"------------------------------------------------------------"<<endl;
        }
    }
}