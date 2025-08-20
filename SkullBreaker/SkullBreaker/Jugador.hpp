#include <SDL3/SDL.h>

class Jugador
{
public:
	void DibujarJugador(SDL_Renderer* render, int x, int y, int ancho, int alto)
	{
		SDL_FRect jugador;
		jugador.x = x;
		jugador.y = y;
		jugador.w = ancho;
		jugador.h = alto;

		SDL_SetRenderDrawColor(render, 255, 255, 0, 0);
		SDL_RenderFillRect(render, &jugador);
		SDL_RenderPresent(render);
	}
};