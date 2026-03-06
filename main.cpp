#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>//字体库
#include <SDL_mixer.h>//音频库
#include <SDL_image.h>//图像库

#include"button.h"

int main(int argc, char* argv[])
{
	std::cout<<"hellow"<< std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_Window* window = SDL_CreateWindow(u8"button example",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,580,720,SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* suf_img = IMG_Load("W:/vs2022/SDLtest/Hit.png");
	SDL_Texture* tex_ing = SDL_CreateTextureFromSurface(renderer,suf_img);

	TTF_Font* font = TTF_OpenFont("W:/vs2022/SDLtest/ipix.ttf",32);
	SDL_Color color = { 0,0,0,255 };//设置颜色
	SDL_Surface* suf_text = TTF_RenderUTF8_Blended(font, "Button",color);
	SDL_Texture* tex_text = SDL_CreateTextureFromSurface(renderer, suf_text);

	SDL_Event event;
	SDL_Point pos_cursor = { 0,0 };

	//--------------------------------------using button----------------------------------------------------
	SDL_Rect rect_button = { 100,50,250,100 };
	SDL_Rect rect_message = { 105,55,240,90 };

	Mix_Chunk* effect_down = Mix_LoadWAV("W:/vs2022/SDLtest/sound_1.wav");
	Mix_Chunk* effect_up= Mix_LoadWAV("W:/vs2022/SDLtest/sound_2.wav");

	Button button_test(renderer, rect_button, rect_message, tex_text, effect_down, effect_up);
	button_test.set_on_click([]
		{
		std::cout << "button on click" << std::endl;
		});

	//---------------------------------------------------------------------------------------------------

	bool is_quit = false;

	int FPS = 60;
	Uint64 last_counter = SDL_GetPerformanceCounter();
	Uint64 counter_freq = SDL_GetPerformanceFrequency();

	while (!is_quit)
	{
		while (SDL_PollEvent(&event))
		{
			button_test.handle_event(event);

			if (event.type == SDL_QUIT)
			{
				is_quit = true;
			}
		}

		Uint64 current_counter = SDL_GetPerformanceCounter();
		double delta = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		if (delta * 1000 < 1000.0 / 60)
			SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));

		SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
		SDL_RenderClear(renderer);

		button_test.render();

		SDL_RenderPresent(renderer);
	}


	return 0;
}
