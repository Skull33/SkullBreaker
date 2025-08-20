#include <iostream>
#include "Jugador.hpp"
#include <SDL3/SDL.h>

using namespace std;

int main()
{
	cout << "Bienvenido a SkullBreaker" << endl;

	SDL_Window* ventana = SDL_CreateWindow("SkullBreaker", 640, 400, NULL);
	bool quitar = false;
	SDL_Renderer* render = SDL_CreateRenderer(ventana, "");
	Jugador p1;
	SDL_Event evento;
	if (ventana == NULL)
	{
		cout << "Error al iniciar la ventna de SkullBreaker" << SDL_GetError() << endl;
		return -1;
	}

	SDL_SetRenderDrawColor(render, 50, 50, 50, 0);
	SDL_RenderClear(render);
	p1.DibujarJugador(render, 100, 100, 5, 5);
	SDL_RenderPresent(render);

	while (!quitar)
	{
		while (SDL_PollEvent(&evento) != 0)
		{
			if (evento.type == SDL_EVENT_QUIT)
			{
				quitar = true;
			}
		}
	}


	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(ventana);
	SDL_Quit();

	return 0;
}