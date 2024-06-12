#include "../include/renderEngine.cpp"

int main()
{
    RenderEngine renderEngine;
    int index;

    uint32_t pixel = 0x000000FF;
    while (true) {
        for (int y = 0; y < renderEngine.getHeight() - 1; y++) {
            for (int x = 0; x < renderEngine.getWidth() - 1; x++) {
                index = (y * renderEngine.getWidth() + x);
                renderEngine.queuePixel(index, pixel);
            }
        }
        renderEngine.updateBuffer();
        if (pixel == 255) {
            pixel = 0;
        } else {
            pixel++;
        }
    }

    return 0;
}