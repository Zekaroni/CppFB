#define SDL_MAIN_HANDLED
#include "../include/sdlWrapper.cpp"
#include "../include/renderEngine.cpp"
#include <chrono>

int main()
{
    int width = 640;
    int height = 480;
    Window window(width, height);
    Framebuffer buffer(width, height);
    RenderEngine renderEngine(buffer);

    int index;

    bool running = true;
    SDL_Event event;

    uint32_t value = 0;
    uint32_t pixel = 0xFFFFFFFF;
    int frameCount = 0;
    double totalTime = 0.0;
    double fps = 0.0;


    int y = 0;
    int cycle = 0;
    uint32_t colours[] = {
        0x00ff0000,
        0x0000ff00,
        0x000000ff
    };

    while (running)
    {
        auto start = std::chrono::high_resolution_clock::now();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        };
        
        y++;
        if (y > renderEngine.framebuffer.getHeight())
        {
            y = 0;
            cycle++;
        }
        renderEngine.drawLine(0,y,renderEngine.framebuffer.getWidth(),y,colours[cycle%3],1);

        window.render(renderEngine.framebuffer.localbuffer);

        frameCount++;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        totalTime += duration.count();
        if (totalTime >= 1.0)
        {
            fps = frameCount / totalTime;
            std::cout << "FPS: " << fps << std::endl;
            frameCount = 0;
            totalTime = 0.0;
        }
    }

    return 0;
}
