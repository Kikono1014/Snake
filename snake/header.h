#include <iostream>
#include <random>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>

#if defined _WIN32
    #include "windows.h"
#elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
    #include <unistd.h>
#endif

#define WIDTH  85
#define HEIGHT 50
