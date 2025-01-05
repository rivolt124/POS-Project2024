//TODO ZATIAL TESTOVACIA VERZIA
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

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