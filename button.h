#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <functional>

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
    explicit Button(SDL_Renderer* renderer, SDL_Rect rect_button);

    Button(SDL_Renderer* renderer, SDL_Rect rect_button, SDL_Rect rect_message, SDL_Texture* texture_message,
        Mix_Chunk* sound_effect_down, Mix_Chunk* sound_effect_up);

    Button(SDL_Renderer* renderer, SDL_Rect rect_button, SDL_Rect rect_message, SDL_Texture* texture_message,
        Mix_Chunk* sound_effect_down, Mix_Chunk* sound_effect_up,
        SDL_Color color_idle, SDL_Color color_hovered, SDL_Color color_pushed, SDL_Color color_frame);

    Button(SDL_Renderer* renderer, SDL_Rect rect_button, SDL_Rect rect_message, SDL_Texture* texture_message,
        Mix_Chunk* sound_effect_down, Mix_Chunk* sound_effect_up,
        SDL_Texture* texture_idle, SDL_Texture* texture_hovered, SDL_Texture* texture_pushed);

    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;
    Button(Button&&) = default;
    Button& operator=(Button&&) = default;
    ~Button() = default;

    void render();
    bool handle_event(const SDL_Event& event);
    void set_button_rect(SDL_Rect new_rect_button);
    void set_message_rect(SDL_Rect new_rect_message);
    void set_message_texture(SDL_Texture* new_texture_message);
    void set_enabled(bool enabled);
    [[nodiscard]] bool is_enabled() const;
    [[nodiscard]] int click_count() const;
    void reset_click_count();
    void set_on_click(std::function<void()> func);
    [[nodiscard]] Status get_status()const;

private:

    bool check_cursor_hit(int x, int y)const;
    bool update_hover_status(int x, int y);
    void init_assert(const void* ptr, const char* err_msg)const;

private:

    // External resources are non-owning; caller must keep them alive.
    SDL_Renderer* renderer = nullptr;

    SDL_Rect rect_button{};
    SDL_Rect rect_message{};

    Mix_Chunk* sound_effect_down = nullptr;
    Mix_Chunk* sound_effect_up = nullptr;

    SDL_Texture* texture_message = nullptr;
    SDL_Texture* texture_idle = nullptr;
    SDL_Texture* texture_hovered = nullptr;
    SDL_Texture* texture_pushed = nullptr;

    SDL_Color color_frame = { 0, 0, 0, 255 };

    SDL_Color color_idle = { 180, 180, 180, 255 };
    SDL_Color color_hovered = { 200, 200, 200, 255 };
    SDL_Color color_pushed = { 130, 130, 130, 255 };

    Status status = Status::Idle;

    std::function<void()> on_click;

    bool have_texture = false;
    bool enabled = true;
    bool is_pressing = false;

    int time_on_click = 0;

};
