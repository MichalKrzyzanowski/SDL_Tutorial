#include "../include/Game.h"

Game::Game() :
	m_gameIsRunning{ false }
{
	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow("SDL tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	TTF_Init();

	m_rect.x = 100;
	m_rect.y = 100;
	m_rect.w = 200;
	m_rect.h = 50;

	m_font = TTF_OpenFont("assets/lazy.ttf", 36);

	m_textureIMG = util::loadFromFileIMG("assets/monke.png", m_renderer);
	m_surfaceBMP = util::loadFromFileBMPSurface("assets/sdl_test.bmp");
	m_text = util::loadText(m_font, "Spoons?", SDL_Color{ 0, 0, 0, 0 }, m_renderer);

	m_currentSurface = SDL_GetWindowSurface(m_window);
}

Game::~Game()
{
	cleanUp();
}

void Game::run()
{
	m_gameIsRunning = true;
	SDL_Event e{};

	while (m_gameIsRunning)
	{
		processEvents(e);
		update();
		render();
	}

	cleanUp();
}

void Game::processEvents(SDL_Event e)
{
	// simple event loop
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			m_gameIsRunning = false;
		}

		// checks if the escape key is pressed down
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
		{
			m_gameIsRunning = false;
		}

		//moveSpoons(e);
	}

}

void Game::update()
{
	//m_rect.x += m_vel.x;
	//m_rect.y += m_vel.y;

	// keystates version
	moonSpoonsKeystate();
}

void Game::render()
{
	// surface stuff
	//surfaceDraw();


	// renderer stuff
	rendererDraw();
}

void Game::surfaceDraw()
{
	SDL_Rect src{ 100, 100, 200, 200 };
	SDL_BlitSurface(m_surfaceBMP, &src, m_currentSurface, nullptr);
	SDL_UpdateWindowSurface(m_window);
}

void Game::rendererDraw()
{
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	SDL_RenderClear(m_renderer);

	SDL_FRect renderSrc{ 0, 0, 0, 0 };
	SDL_FRect renderDest{ 5, 5, 200, 100 };

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderCopyF(m_renderer, m_textureIMG, nullptr, nullptr);
	SDL_RenderCopyF(m_renderer, m_text, nullptr, &m_rect);
	SDL_RenderDrawRectF(m_renderer, &m_rect);
	SDL_RenderPresent(m_renderer);
}

void Game::moveSpoons(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_w)
		{
			m_vel.y = -MAX_VEL;
		}

		if (e.key.keysym.sym == SDLK_s)
		{
			m_vel.y = MAX_VEL;
		}

		if (e.key.keysym.sym == SDLK_a)
		{
			m_vel.x = -MAX_VEL;
		}

		if (e.key.keysym.sym == SDLK_d)
		{
			m_vel.x = MAX_VEL;
		}
	}
	if (e.type == SDL_KEYUP)
	{
		if (e.key.keysym.sym == SDLK_w)
		{
			m_vel.y = 0;
		}

		if (e.key.keysym.sym == SDLK_s)
		{
			m_vel.y = 0;
		}

		if (e.key.keysym.sym == SDLK_a)
		{
			m_vel.x = 0;
		}

		if (e.key.keysym.sym == SDLK_d)
		{
			m_vel.x = 0;
		}
	}
}

void Game::moonSpoonsKeystate()
{
	m_rect.x = m_vel.x;
	m_rect.y = m_vel.y;

	const Uint8* keystates = SDL_GetKeyboardState(nullptr);

	if (keystates[SDL_SCANCODE_W])
	{
		m_vel.y -= MAX_VEL;
	}

	if (keystates[SDL_SCANCODE_S])
	{
		m_vel.y += MAX_VEL;
	}

	if (keystates[SDL_SCANCODE_A])
	{
		m_vel.x -= MAX_VEL;
	}

	if (keystates[SDL_SCANCODE_D])
	{
		m_vel.x += MAX_VEL;
	}
}

void Game::cleanUp()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	m_renderer = nullptr;

	SDL_DestroyTexture(m_textureIMG);
	SDL_DestroyTexture(m_text);
	SDL_FreeSurface(m_surfaceBMP);
	SDL_FreeSurface(m_currentSurface);
	m_textureIMG = nullptr;
	m_surfaceBMP = nullptr;
	m_currentSurface = nullptr;
	m_text = nullptr;

	TTF_CloseFont(m_font);
	m_font = nullptr;

	IMG_Quit();
	SDL_Quit();
}