class SnakeFood {
private:
    int x;
    int y;
public:

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    void setFood(int max_x, int max_y) {
        setX(random(0, max_x));
        setY(random(0, max_y));
    }

    void drawFood(
                        string (&frameBuffer)[HEIGHT][WIDTH],
                        string value,
                        RGB color, TextStyle type, TextStyle style = NONE
                        )
    {
        Drawer::SetPoint(frameBuffer, getX(), getY(), value, color, type, style);
    }




    bool updateFood(Snake snake, int max_x, int max_y) {
        if (
            (snake.getSnakeBodyPartX(0) == x)
            &&
            (snake.getSnakeBodyPartY(0) == y)
            ) {
            setFood(max_x, max_y);
            return 1;
        } else {
            return 0;
        }
    }
};
