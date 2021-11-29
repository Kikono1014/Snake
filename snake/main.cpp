#include "header.h"
#include "TextStyle/TextStyle.h"
#include "Drawer/Drawer.h"
#include "Drawer/Sprite.h"
#include "Frame/Frame.h"

using namespace std;
using namespace stl;

int random(int min, int max) {
    random_device rd;
    mt19937 mersenne(rd());
    int random = mersenne() % max + min;
    return random;
}

double framerate = 20.0;
string frameBuffer[HEIGHT][WIDTH];
Frame frame(framerate);

#include "Snake/Snake.h"
#include "Food/Food.h"

int _keyInterrupt() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

   int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

int main() {
    int width = WIDTH;
    int height = HEIGHT;

    Snake snake(10, 2, 5, "right");
    snake.start();

    SnakeFood food;
    food.setFood(width-1, height-1);

    string command = " ";

    while (true) {

        Drawer::SetLine(frameBuffer, Point(0, 0, "  ", RGB(90, 13, 172), BG_RGB), Point(width-1, 0, "  ", RGB(90, 13, 172), BG_RGB));
        Drawer::SetLine(frameBuffer, Point(width-1, 0, "  ", RGB(90, 13, 172), BG_RGB), Point(width-1, height-1, "  ", RGB(90, 13, 172), BG_RGB));
        Drawer::SetLine(frameBuffer, Point(width-1, height-1, "  ", RGB(90, 13, 172), BG_RGB), Point(0, height-1, "  ", RGB(90, 13, 172), BG_RGB));
        Drawer::SetLine(frameBuffer, Point(0, height-1, "  ", RGB(90, 13, 172), BG_RGB), Point(0, 0, "  ", RGB(90, 13, 172), BG_RGB));

        snake.updateMoveDirection();
        if (food.updateFood(snake, width-1, height-1)) {
            snake.growSnake();
        }

        snake.drawSnake(frameBuffer, "  ", RGB(0, 200, 200), BG_RGB);
        food.drawFood  (frameBuffer, "  ", RGB(200, 0, 0), BG_RGB);

        if(_keyInterrupt()) {
           command = getchar();
        }

        snake.changeMoveDirection(command);

        frame.presentFrame(width, height, frameBuffer);
        frame.updateFrame(width, height, frameBuffer);

    }

    return 0;
}


