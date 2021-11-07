class Drawer {
public:
    static string **SetPoint(int x, int y, TextStyle color, string **frameBuffer) {
        frameBuffer[y][x] = Text::setStyle("  ", FG_DEFAULT, color);
        return frameBuffer;
    }


    static string **SetLine(int x0, int y0, int x1, int y1, TextStyle color, string **frameBuffer) {
        int deltaX = x1 - x0;
        int deltaY = y1 - y0;
        int absDeltaX = abs(deltaX);
        int absDeltaY = abs(deltaY);

        int accretion = 0;

        int centerX = (int)(absDeltaX / 2);
        int centerY = (int)(absDeltaY / 2);

        if (absDeltaX >= absDeltaY) {
            int y = y0;
            int const direction = deltaY != 0 ? (deltaY > 0 ? 1 : -1) : 0;
            for (int x = x0; deltaX > 0 ? x <= x1 : x >= x1; deltaX > 0 ? x++ : x--) {
                frameBuffer = SetPoint(x, y, color, frameBuffer);
                accretion += absDeltaY;

                if (accretion >= absDeltaX) {
                    accretion -= absDeltaX;
                    y += direction;
                }
            }
        } else {
            int x = x0;
            const int direction = deltaX != 0 ? (deltaX > 0 ? 1 : -1) : 0;
            for (int y = y0; deltaY > 0 ? y <= y1 : y >= y1; deltaY > 0 ? y++ : y--) {
                frameBuffer = SetPoint(x, y, color, frameBuffer);
                accretion += absDeltaX;

                if (accretion >= absDeltaY) {
                    accretion -= absDeltaY;
                    x += direction;
                }
            }
        }
        return frameBuffer;
    }

    static string **SetSquare(int x0, int y0, int width, int height, TextStyle color, string **frameBuffer) {
        int x1 = x0 - (int)(width / 2);
        int x2 = x0 + (int)(width / 2);
        int y1 = y0 - (int)(height / 2);
        int y2 = y0 + (int)(height / 2);
        frameBuffer = SetLine(x1, y1, x2, y1, color, frameBuffer);
        frameBuffer = SetLine(x1, y2, x2, y2, color, frameBuffer);
        frameBuffer = SetLine(x1, y1, x1, y2, color, frameBuffer);
        frameBuffer = SetLine(x2, y1, x2, y2, color, frameBuffer);
        return frameBuffer;
    }
};
