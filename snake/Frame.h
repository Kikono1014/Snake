#if defined _WIN32
    #include "windows.h"
#elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
    #include <unistd.h>
#endif
class Frame {
public:
    unsigned int width;
    unsigned int height;

    Frame(int width, int height) {
        this->width = width;
        this->height = height;
    }

    int getWidth()  { return this->width; }
    int getHeight() { return this->height; }

    string **createFrameBuffer(int width, int height, string **frameBuffer) {
        frameBuffer = new string * [height];
        for (int i = 0; i < height; i++) {
            frameBuffer[i] = new string [width];
        }
        return frameBuffer;
    }

    void delay(double time) {
        #if defined _WIN32
            Sleep(time * 1000);
        #elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
            usleep(time * 1000000);
        #endif
    }

    void clear() {

        #if defined _WIN32
            system("cls");
        #elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
            system("clear");
        #elif defined (__APPLE__)
            system("clear");
        #endif
    }

    void presentFrame(int width, int height, string **frameBuffer) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cout << frameBuffer[y][x];
            }
            cout << endl;
        }
    }

    string **reset(int width, int height, string **frameBuffer) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                frameBuffer[y][x] = "  ";
            }
        }
        return frameBuffer;
    }

    string **updateFrame(int width, int height, string **frameBuffer) {
        delay(1 / 30.0);
        reset(width, height, frameBuffer);
        clear();
        return frameBuffer;
    }
};
