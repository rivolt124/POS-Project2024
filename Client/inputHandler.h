#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

void enableRawMode();
void disableRawMode();
int isKeyPressed();
char init_inputHandler();

#endif