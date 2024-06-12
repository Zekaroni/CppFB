#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <chrono>

class RenderEngine
{
public:
    void queuePixel(int index, uint32_t pixel)
    {
        localbuffer[index] = pixel;
    };

    void updateBuffer()
    {
        framebuffer.seekp(0, std::ios_base::beg);
        framebuffer.write(reinterpret_cast<char*>(localbuffer), TOTAL_PIXELS * sizeof(uint32_t));
    };

    void writeBuffer(uint32_t buffer[], size_t size)
    {
        framebuffer.seekp(0, std::ios_base::beg);
        framebuffer.write(reinterpret_cast<char*>(buffer), size * sizeof(uint32_t));
    };

    void fillBuffer(uint32_t pixel)
    {
        for (int i = 0; i < TOTAL_PIXELS; ++i)
        {
            localbuffer[i] = pixel;
        }
    };

    int getWidth()
    {
        return WIDTH;
    };

    int getHeight()
    {
        return HEIGHT;
    };

    int getTotalPixels()
    {
        return TOTAL_PIXELS;
    };

    RenderEngine()
    {
        initFramebuffer();
        initScreenSize();
        localbuffer = new uint32_t[WIDTH * HEIGHT];
    };

    ~RenderEngine() {
        delete[] localbuffer;
    };

private:
    std::fstream framebuffer;
    const char* FRAMEBUFFER_PATH = "/dev/fb0";
    uint16_t WIDTH, HEIGHT;
    uint32_t TOTAL_PIXELS;
    uint32_t* localbuffer;

    void initFramebuffer()
    {
        framebuffer.open(FRAMEBUFFER_PATH, std::ios::in | std::ios::out);
        if (!framebuffer.is_open())
        {
            std::cerr << "Error opening /dev/fb0" << std::endl;
            exit(1);
        }
    };

    void initScreenSize()
    {
        std::fstream SYS_SIZE_FILE("/sys/class/graphics/fb0/virtual_size");
        if (!SYS_SIZE_FILE.is_open())
        {
            std::cerr << "Error opening /sys/class/graphics/fb0/virtual_size" << std::endl;
            exit(1);
        }
        std::string contents;
        std::getline(SYS_SIZE_FILE, contents);
        char comma;
        std::istringstream iss(contents);
        iss >> WIDTH >> comma >> HEIGHT;
        SYS_SIZE_FILE.close();
        TOTAL_PIXELS = WIDTH * HEIGHT;
    };
};
