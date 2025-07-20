#include <ncurses.h>

int main(void) {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_CYAN);
    attron(COLOR_PAIR(1));
    printw("Pair slots count: %d\n", COLOR_PAIRS);
    attroff(COLOR_PAIR(1));
    printw("Color slots count: %d\n", COLORS);
    refresh();
    getch();
    endwin();
}
