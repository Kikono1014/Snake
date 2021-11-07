class SnakeBodyPart {
public:
    int x;
    int y;
    string moveDirection;
    string nextMoveDirection;

    SnakeBodyPart() {}
    SnakeBodyPart(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() { return x; }
    int getY() { return y; }
    string getMoveDirection() { return moveDirection; }
    string getNextMoveDirection() { return nextMoveDirection; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setMoveDirection(string newDirection) { moveDirection = newDirection; }
    void setNextMoveDirection(string newDirection) { nextMoveDirection = newDirection; }
};


class Snake {
public:
    int x;
    int y;
    int len;
    string moveDirection;
    SnakeBodyPart *body;

    Snake (int x, int y, int len, string moveDirection) {
        this->x = x;
        this->y = y;
        this->len = len;
        SnakeBodyPart *newArr = new SnakeBodyPart [len];
        body = newArr;
        for (int i = 0; i < len; i++) {
            SnakeBodyPart newBodyPart(x-i, y);
            body[i] = newBodyPart;
        }
        this->moveDirection = moveDirection;
    }

    int getLen() { return len; };
    int getSnakeBodyPartX(int i) { return body[i].getX(); };
    int getSnakeBodyPartY(int i) { return body[i].getY(); };

    void setMoveDirection(string newDirection) {
        moveDirection = newDirection;
    }

    void growSnake () {
        len++;
        x = body[len-2].getX();
        y = body[len-2].getY();

        SnakeBodyPart *newArr = new SnakeBodyPart [len];
        for (int i = 0; i < len-1; i++)
            newArr[i] = body[i];

        SnakeBodyPart newBodyPart(x, y);
        newArr[len-1] = newBodyPart;
        body = newArr;
    }

    void moveSnake() {
        for (int i = 0; i < len; i++) {
            if (body[i].getMoveDirection() == "up") {
                int y = body[i].getY();
                body[i].setY(y -= 1);
            }
            else if (body[i].getMoveDirection() == "left") {
                int x = body[i].getX();
                body[i].setX(x -= 1);
            }
            else if (body[i].getMoveDirection() == "down") {
                int y = body[i].getY();
                body[i].setY(y += 1);
            }
            else if (body[i].getMoveDirection() == "right") {
                int x = body[i].getX();
                body[i].setX(x += 1);
            }
            body[i].setMoveDirection(body[i].getNextMoveDirection());
        }
    }

    void start() {
        for (int i = 0; i < len; i++) {
            body[i].setMoveDirection(moveDirection);
            body[i].setNextMoveDirection(moveDirection);
        }
    }
    void updateMoveDirection() {
        body[0].setMoveDirection(moveDirection);
        for (int i = 1; i < len; i++) {
            body[i].setNextMoveDirection(body[i-1].getMoveDirection());
        }
        moveSnake();
    }

    void changeMoveDirection() {
        string command;
        cin >> command;
        if      (command == "w")
            setMoveDirection("up");
        else if (command == "a")
            setMoveDirection("left");
        else if (command == "s")
            setMoveDirection("down");
        else if (command == "d")
            setMoveDirection("right");
    }

    string **drawSnake(string **frameBuffer) {
        for (int i = 0; i < len; i++) {
            int x = getSnakeBodyPartX(i);
            int y = getSnakeBodyPartY(i);
            frameBuffer = Drawer::SetPoint(x, y, BG_CYAN, frameBuffer);
        }
        return frameBuffer;
    }
};
