#include "Utility.h"

void utilities::PrintStringAt(COORD _position, std::string _text)
{
	SetConsoleCursorPosition(consoleHandle, _position);

	std::cout << _text;
}

void utilities::PrintCharAt(COORD _position, char _text)
{
	SetConsoleCursorPosition(consoleHandle, _position);

	std::cout << _text;
}

void utilities::TranslatePos(COORD& _ToSwap, COORD _translateFrom)
{
	COORD newPos;
	newPos.X = _translateFrom.X + _ToSwap.X;
	newPos.Y = _translateFrom.Y + _ToSwap.Y;
	_ToSwap = newPos;
}

void utilities::SetConsoleColor(ConsoleColor _foreground, ConsoleColor _background = Black) //NSM
{
	WORD colorAttribute = static_cast<WORD>(_foreground) | (static_cast<WORD>(_background) << 4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorAttribute);
}

// Maximize console window like clicking the top-right button
void utilities::SetToFullScreen() 
{
    HWND consoleWindow = GetConsoleWindow(); 
    ShowWindow(consoleWindow, SW_RESTORE);// Minimize so Maximize doesn't get skipped (This gets skiped if already Minimized)

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD tiny = { 10, 10 };
    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(tiny.X - 1), static_cast<SHORT>(tiny.Y - 1) }; 
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);// Reduce console window size so buffer can do the same
    SetConsoleScreenBufferSize(hConsole, tiny); // Reduce buffer size so it can get reajusted with Maximize


    ShowWindow(consoleWindow, SW_MAXIMIZE); // Maximize to go full-screen with no scrollbar
}

void utilities::SetFontSize(short _width, short _height) //NSM
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };
    cfi.nFont = 0;
    cfi.dwFontSize.X = _width;  // Character width
    cfi.dwFontSize.Y = _height; // Character height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas"); // or L"Lucida Console"

    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

std::vector<int>* utilities::GetConsoleSize() //NSM
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    std::vector<int>* windowSize = new std::vector<int>();
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        windowSize->push_back(csbi.srWindow.Right - csbi.srWindow.Left + 1);
        windowSize->push_back(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
    }
    return windowSize;
}

COORD utilities::CenterTextX(std::string _text, int _y) 
{
    COORD pos;
    pos.Y = _y;
    pos.X = (utilities::GetConsoleSize()->at(0) / 2) - (_text.size() / 2);
    if (utilities::GetConsoleSize()) delete utilities::GetConsoleSize();
    return pos;
}

void utilities::SetCursorPos(int& _X, int& _Y) 
{
    COORD pos;
    pos.X = _X;
    pos.Y = _Y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

void utilities::ClearConsoleLine(short _y) //NSM
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    DWORD consoleWidth = csbi.dwSize.X;
    COORD lineStart = { 0, _y };
    DWORD charsWritten;

    // Fill the line with spaces
    FillConsoleOutputCharacter(hConsole, ' ', consoleWidth, lineStart, &charsWritten);

    // Reset attributes
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleWidth, lineStart, &charsWritten);

    // Move cursor to start of the line
    SetConsoleCursorPosition(hConsole, lineStart);
}

void utilities::SetCursorVisible(bool _visible) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    cursorInfo.bVisible = _visible;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

std::string utilities::ReadCenteredInput(short _centerY, int _consoleWidth) //NSM
{ 
    std::string input;
    bool done = false;

    while (!done) {
        // Clear line
        COORD clearPos = { 0, _centerY };
        DWORD written;
        FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', _consoleWidth, clearPos, &written);

        // Calculate center X
        short centerX = (_consoleWidth - static_cast<short>(input.length())) / 2;

        // Print input centered
        COORD inputPos = { centerX, _centerY };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), inputPos);
        std::cout << input;

        // Set cursor at end
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(centerX + input.length()), _centerY });

        // Read key
        char ch = _getch();

        if (ch == '\r') { // Enter
            done = true;
        }
        else if (ch == '\b') { // Backspace
            if (!input.empty()) {
                input.pop_back();
            }
        }
        else if (isprint(ch)) {
            input += ch;
        }
    }

    return input;
}
