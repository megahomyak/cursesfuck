#include <ncurses.h>

int main(void) {
    initscr();
    printw("Hello, world!");
    refresh();
    getch();
    endwin();
}
