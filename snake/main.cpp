#include <iostream>
#include <random>
#include "textstyle.h"

using namespace std;
using namespace stl;

#include "Frame.h"

int random(int min, int max) {
    random_device rd;
    mt19937 mersenne(rd());
    int random = mersenne() % max + min;
    return random;
}

unsigned int width = 85;
unsigned int height = 50;
string **frameBuffer;
Frame frame(width, height);

#include "Drawer.h"
#include "Snake.cpp"
#include "Food.cpp"


int main() {
    int width = frame.width;
    int height = frame.height;

    frameBuffer = frame.createFrameBuffer(width, height, frameBuffer);

    frame.presentFrame(width, height, frameBuffer);
    frameBuffer = frame.updateFrame(width, height, frameBuffer);

    Snake snake(10, 2, 5, "right");
    snake.start();

    SnakeFood food;
    food.setFood(width-1, height-1);

    string command = " ";

    while (true) {
        snake.updateMoveDirection();
        if (food.updateFood(snake, width-1, height-1)) {
            snake.growSnake();
        }

        frameBuffer = snake.drawSnake(frameBuffer);
        frameBuffer = food.drawFood(frameBuffer);

        frame.presentFrame(width, height, frameBuffer);

        snake.changeMoveDirection();

        frameBuffer = frame.updateFrame(width, height, frameBuffer);

    }

    return 0;
}


