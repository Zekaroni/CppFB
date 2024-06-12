#include "../include/sdlWrapper.cpp"

int main()
{
    Window window;

    bool running = true;
    SDL_Event event;

    uint32_t value = 0;
    std::vector<uint32_t> framebuffer(640 * 480, value);

    int shiftAmount[3] = {0,8,16};
    while (true)
    {
        for (int o = 0; o < 3; o++)
        {
            for (int i = 0; i < 255; i++)
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        return 1;
                    }
                }

                window.clearScreen();
                std::fill(framebuffer.begin(), framebuffer.end(), i << shiftAmount[o]);
                window.render(framebuffer);
                SDL_Delay(15);
            }
        }
    }

    return 0;
}

