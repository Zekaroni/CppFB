#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstring>

class Window
{
public:
    Window(int W, int H)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return;
        }

        // Name, X, Y, W, H, Flags
        win = SDL_CreateWindow("Render Tester", 100, 100, W, H, SDL_WINDOW_SHOWN);
        if (win == nullptr)
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (ren == nullptr)
        {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(win);
            SDL_Quit();
            return;
        }

        tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
        if (tex == nullptr)
        {
            std::cerr << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            SDL_Quit();
            return;
        }
    }

    ~Window()
    {
        destroy();
    }

    void destroy()
    {
        if (tex) SDL_DestroyTexture(tex);
        if (ren) SDL_DestroyRenderer(ren);
        if (win) SDL_DestroyWindow(win);
        SDL_Quit();
    }

    void clearScreen()
    {
        SDL_RenderClear(ren);
    }

    void render(const std::vector<uint32_t>& framebuffer)
    {
        uint32_t* pixels = nullptr;
        int pitch = 0;
        SDL_LockTexture(tex, nullptr, (void**)&pixels, &pitch);
        std::memcpy(pixels, framebuffer.data(), framebuffer.size() * sizeof(uint32_t));
        SDL_UnlockTexture(tex);
        SDL_RenderCopy(ren, tex, nullptr, nullptr);
        SDL_RenderPresent(ren);
    }

private:
    SDL_Window* win = nullptr;
    SDL_Renderer* ren = nullptr;
    SDL_Texture* tex = nullptr;
};