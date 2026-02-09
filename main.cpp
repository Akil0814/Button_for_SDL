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

	SDL_Init(SDL_INIT_EVERYTHING);//初始化
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);//初始化图像格式
	Mix_Init(MIX_INIT_MP3);//初始化音频库
	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);//打开声道

	SDL_Window* window = SDL_CreateWindow(u8"button example",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1280,720,SDL_WINDOW_SHOWN);//创建窗口
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//创建渲染器

	SDL_Surface* suf_img = IMG_Load("W:/vs2022/SDLtest/Hit.png");//将图片加载到内存中
	SDL_Texture* tex_ing = SDL_CreateTextureFromSurface(renderer,suf_img);//将内存中的图片通过渲染器变成纹理数据

	TTF_Font* font = TTF_OpenFont("W:/vs2022/SDLtest/ipix.ttf",32);//加载字体对象
	SDL_Color color = { 0,0,0,255 };//设置颜色
	SDL_Surface* suf_text = TTF_RenderUTF8_Blended(font, "Button",color);
	SDL_Texture* tex_text = SDL_CreateTextureFromSurface(renderer, suf_text);//创建字体纹理

	SDL_Event event;//交互事件
	SDL_Point pos_cursor = { 0,0 };//记录鼠标位置
	SDL_Rect rect_img;
	SDL_Rect rect_text;


	/////test button///////////////////////////////////////////////
	SDL_Rect rect_button = { 100,50,250,100 };
	SDL_Rect rect_message = { 105,55,240,90 };

	Mix_Chunk* effect_down = Mix_LoadWAV("W:/vs2022/SDLtest/sound_1.wav");
	Mix_Chunk* effect_up= Mix_LoadWAV("W:/vs2022/SDLtest/sound_2.wav");

	Button button_test(renderer, rect_button, rect_message, tex_text, effect_down, effect_up);
	button_test.set_on_click([]
		{
		std::cout << "button on click" << std::endl;
		});

	///////////////////////////////////////////////////////////////


	rect_img.w = suf_img->w;//获取图片的宽高 存入SDL_Rect
	rect_img.h = suf_img->h;

	rect_text.w = suf_text->w;
	rect_text.h = suf_text->h;

	bool is_quit = false;

	int FPS = 60;
	Uint64 last_counter = SDL_GetPerformanceCounter();//计数器计数总数
	Uint64 counter_freq = SDL_GetPerformanceFrequency();//获取高性能计数器的频率

	while (!is_quit)
	{
		while (SDL_PollEvent(&event))//拉取事件
		{
			button_test.process_event(event);/////test button

			if (event.type == SDL_QUIT)
			{
				//is_quit = true;
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				pos_cursor.x = event.motion.x;
				pos_cursor.y = event.motion.y;
			}
		}

		Uint64 current_counter = SDL_GetPerformanceCounter();//实现动态延时
		double delta = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		if (delta * 1000 < 1000.0 / 60)
			SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));

		rect_img.x = pos_cursor.x;
		rect_img.y = pos_cursor.y;

		rect_text.x = pos_cursor.x;
		rect_text.y = pos_cursor.y;

		SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);//设置窗口背景
		SDL_RenderClear(renderer);//清理窗口

		button_test.on_render();/////test button

		SDL_RenderPresent(renderer);//将渲染数据展示到窗口上
	}


	return 0;
}
