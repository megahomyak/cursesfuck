#include <ncurses.h>

int main(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    printw("Hello, world!");
    refresh();
    for (;;) printw("%c", getch());
    endwin();
}
