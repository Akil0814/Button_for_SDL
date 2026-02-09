#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include<string>
#include<iostream>
#include<functional>

class Button
{
public:
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};

public:

	Button(SDL_Renderer* renderer,SDL_Rect rect_button, SDL_Rect rect_message, SDL_Texture* texture_message,
			Mix_Chunk* sound_effect_down, Mix_Chunk* sound_effect_up);

	Button(SDL_Renderer* renderer, SDL_Rect rect_button, SDL_Rect rect_message, SDL_Texture* texture_message,
			Mix_Chunk* sound_effect_down, Mix_Chunk* sound_effect_up,
			SDL_Color color_idle,SDL_Color color_hovered, SDL_Color color_pushed, SDL_Color color_frame);

	Button(SDL_Renderer* renderer, SDL_Rect rect_button, SDL_Rect rect_message, SDL_Texture* texture_message,
			Mix_Chunk* sound_effect_down, Mix_Chunk* sound_effect_up,
			SDL_Texture* texture_idle,SDL_Texture* texture_hovered, SDL_Texture* texture_pushed);

	~Button() = default;

	void on_render();
	void process_event(const SDL_Event& event);
	void set_on_click(std::function<void()> func);
	void set_status(Status status);

	void change_rect_button(SDL_Rect new_rect_button);
	void change_rect_message(SDL_Rect new_rect_message);
	void change_texture_message(SDL_Texture* new_texture_message);

	void set_on_hold();
	void reset_on_hold();

	int get_time_on_click()const;
	Status get_status()const;
	bool check_on_hold()const;

private:

	bool check_cursor_hit(int x, int y)const;

	template<typename T>
	void init_assert(T* ptr, const std::string& err_msg)const;

private:

	SDL_Renderer* renderer = nullptr;

	SDL_Rect rect_button;
	SDL_Rect rect_message;

	Mix_Chunk* sound_effect_down = nullptr;//“Ù–ß
	Mix_Chunk* sound_effect_up = nullptr;//“Ù–ß

	SDL_Texture* texture_message = nullptr;
	SDL_Texture* texture_idle = nullptr;
	SDL_Texture* texture_hovered = nullptr;
	SDL_Texture* texture_pushed = nullptr;

	SDL_Color color_frame = { 0,0,0,255 };


	SDL_Color color_idle = { 180, 180, 180, 255 };
	SDL_Color color_hovered = { 200, 200, 200, 255 };
	SDL_Color color_pushed = { 130, 130, 130, 255 };

	Status status = Status::Idle;

	std::function<void()> on_click = nullptr;

	bool have_sound_effect_down = false;
	bool have_sound_effect_up = false;

	bool have_texture = false;
	bool have_message = false;

	bool on_hold = false;

	int time_on_click = 0;

};
