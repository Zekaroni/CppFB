#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cmath>

class Framebuffer
{
public:
    std::vector<uint32_t> localbuffer;
    Framebuffer(int width, int height)
    {
        WIDTH = width;
        HEIGHT = height;
        localbuffer.resize(WIDTH * HEIGHT);
    }

    int getWidth()
    {
        return WIDTH;
    };

    int getHeight()
    {
        return HEIGHT;
    };

private:
    int WIDTH;
    int HEIGHT;
};

class RenderEngine
{
public:
    Framebuffer& framebuffer;

    void queuePixel(int index, uint32_t colour)
    {
        framebuffer.localbuffer[index] = colour;
    };

    void fillBuffer(uint32_t pixel)
    {
        std::fill(framebuffer.localbuffer.begin(), framebuffer.localbuffer.end(), pixel);
    };

    int getArrayIndex(int x, int y)
    {
        return y * framebuffer.getWidth() + x;
    };


    // DRAWING FUNCTIONS
    void drawLine(double startX, double startY, double endX, double endY, uint32_t colour, int thickness = 3)
    {
        double slope = (endY - startY) / (endX - startY);
        double c = startY - slope * startX;
        for (double x = startX; x <= endY; ++x)
        {
            for (double i = 0; i<= thickness; ++i)
            {
                double y = round(slope*(x+i)+c);
                int index = getArrayIndex(static_cast<int>(x),static_cast<int>(y));
                queuePixel(index, colour);
            }
        }
    };


    RenderEngine(Framebuffer& fb) : framebuffer(fb)
    {

    };

    ~RenderEngine() = default;
};
