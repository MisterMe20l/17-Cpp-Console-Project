#pragma once
#include <vector>
#include <windows.h>
#include <string>
#include <conio.h>
#include <iostream>

namespace utilities
{
    enum ConsoleColor {
        Black = 0,
        Blue = 1,
        Green = 2,
        Aqua = 3,
        Red = 4,
        Purple = 5,
        Yellow = 6,
        Gray = 8,

        LightGray = 7,
        LightBlue = 9,
        LightGreen = 10,
        LightAqua = 11,
        LightRed = 12,
        LightPurple = 13,
        LightYellow = 14,
        White = 15
    };

    static HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    void PrintStringAt(COORD _position, std::string _text);
    void PrintCharAt(COORD _position, char _char);
    void TranslatePos(COORD& _ToSwap, COORD _roomPos);
    void SetConsoleColor(ConsoleColor _foreground, ConsoleColor _background);

    void SetToFullScreen();
    void SetFontSize(short _width, short _height);
    std::vector<int>* GetConsoleSize();
    COORD CenterTextX(std::string _text, int _y);
    void SetCursorPos(int& _X, int& _Y);
    void ClearConsoleLine(short _y);
    void SetCursorVisible(bool _visible);
    std::string ReadCenteredInput(short _centerY, int _consoleWidth);
};