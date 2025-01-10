//TODO ZATIAL TESTOVACIA VERZIA
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef _WIN32
#include <stdio.h>
#include <windows.h>
#include <conio.h>

// Vypnutie buffrovania a nastavenie "raw mode"
void enableRawMode() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); // Získanie popisovača konzoly
    DWORD mode;
    GetConsoleMode(hStdin, &mode); // Získanie aktuálneho režimu

    // Vypnutie režimov pre ekvivalent raw módu
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    SetConsoleMode(hStdin, mode);
}

// Obnovenie pôvodného buffrovania
void disableRawMode() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); // Získanie popisovača konzoly
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    // Povoľte späť štandardné režimy
    mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    SetConsoleMode(hStdin, mode);
}

// Podpora neblokujúceho režimu
int isKeyPressed() {
    return _kbhit(); // Funkcia z conio.h, ktorá signalizuje, či bol stlačený kláves
}

// Spracovanie vstupu
char init_inputHandler() {
    enableRawMode();
    printf("Stlačte klávesy (q na ukončenie):\n");

    char ch = '\0';
    while (1) {
        if (isKeyPressed()) { // Skontrolujte, či bol nejaký kláves stlačený
            ch = _getch();    // Prečítajte znak (bez blokovania)
            printf("Stlačili ste: %c\n", ch);
            if (ch == 'q') {  // Ukončenie pri stlačení 'q'
                break;
            }
        }
        Sleep(10); // Zníženie záťaže CPU
    }

    disableRawMode();
    return ch;
}

int main() {
    init_inputHandler();
    return 0;
}
#else
// Vypnutie buffrovania a nastavenie "non-blocking" režimu
void enableRawMode() {
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Obnovenie pôvodných nastavení
void disableRawMode() {
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Non-blocking režim pre vstup
void setNonBlockingMode() {
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

char init_inputHandler() {
	enableRawMode();
	setNonBlockingMode();

	printf("Stlačte klávesy (q na ukončenie):\n");

	char ch;
	if (read(STDIN_FILENO, &ch, 1) > 0) {  // Prečíta kláves (non-blocking)
		printf("Stlačili ste: %c\n", ch);
		usleep(10000);  // Udržiava nízku záťaž CPU
	}

	disableRawMode();
	return ch;



}
#endif