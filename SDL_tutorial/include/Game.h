#include <SDL.h>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Utility.h"

struct Vector2f
{
	float x, y;
};

class Game
{
public:

	Game();
	~Game();
	void run();

private:

	void processEvents(SDL_Event e);
	void update();
	void render();
	void surfaceDraw();
	void rendererDraw();

	void moveSpoons(SDL_Event e);

	void cleanUp();

	bool m_gameIsRunning;

	const int WINDOW_WIDTH{ 640 };
	const int WINDOW_HEIGHT{ 480 };

	const float MAX_VEL{ 10 };
	Vector2f m_vel{};

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_FRect m_rect;

	SDL_Texture* m_textureIMG{ nullptr };

	SDL_Surface* m_currentSurface{ nullptr };
	SDL_Surface* m_surfaceBMP{ nullptr };

	SDL_Texture* m_text{ nullptr };
	TTF_Font* m_font{ nullptr };

};