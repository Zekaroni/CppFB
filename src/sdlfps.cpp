#include "../include/sdlWrapper.cpp"
#include <iostream>

int main()
{
    Window window;
    bool running = true;
    SDL_Event event;
    uint32_t value = 0;
    std::vector<uint32_t> framebuffer(640 * 480, value);
    int shiftAmount[3] = {0, 8, 16};
    int frameCount = 0;
    float fpsTimer = 0.0f;
    float deltaTime = 0.0f;
    const float targetFrameTime = 1000.0f / 60.0f;
    while (true)
    {
        Uint32 frameStart = SDL_GetTicks();
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
                frameCount++;
            }
        }
        Uint32 frameEnd = SDL_GetTicks();
        deltaTime = frameEnd - frameStart;
        fpsTimer += deltaTime;
        if (fpsTimer >= 1000.0f)
        {
            float fps = frameCount / (fpsTimer / 1000.0f);
            std::cout << "FPS: " << fps << std::endl;
            frameCount = 0;
            fpsTimer = 0.0f;
        }
        if (deltaTime < targetFrameTime)
        {
            SDL_Delay((Uint32)(targetFrameTime - deltaTime));
        }
    }
    return 0;
}
