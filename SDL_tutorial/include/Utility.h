#ifndef UTILITY_H
#define UTILITY_H

namespace util
{
	inline SDL_Texture* loadFromFileIMG(const char* const path, SDL_Renderer* renderer)
	{
		SDL_Texture* newTexture{ NULL };

		SDL_Surface* loadedSurface = IMG_Load(path);
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
		}
		else
		{
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
			}

			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;
	}

	inline SDL_Surface* loadFromFileBMPSurface(const char* const path)
	{
		SDL_Surface* loadedSurface = SDL_LoadBMP(path);
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path, SDL_GetError());
		}
		
		return loadedSurface;
	}

	inline SDL_Texture* loadText(TTF_Font* font, const char* const string, SDL_Color color, SDL_Renderer* renderer)
	{
		SDL_Texture* newTexture{ NULL };

		SDL_Surface* textSurface = TTF_RenderText_Solid(font, string, color);
		if (textSurface != NULL)
		{
			newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}

			SDL_FreeSurface(textSurface);
		}
		else
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}

		return newTexture;
	}
}
#endif // !UTILITY_H