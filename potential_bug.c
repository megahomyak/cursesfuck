// bug repro for Kitty
//
// BUG INFO:
// The specified cell will get skipped visually if (the bottom right corner of the terminal contains any non-whitespace character or a character written with any attr (?)) and there was no refresh() before the move().

#include <ncurses.h>
#include <stdbool.h>

enum APPROACH {
    ATTRON,
    NON_WHITESPACE,
};

int main(void) {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    int cursor_x = 0;
    bool the_bug_is_on = true;

    const int MAGIC_OFFSET_WHERE_CURSOR_BREAKS = 5; // DO NOT EDIT

    const enum APPROACH approach = ATTRON; // Edit freely
    const bool show_getcur = true; // Edit freely

    while (1) {
        const int max_y = getmaxy(stdscr) - 1;
        const int scr_width = getmaxx(stdscr);
        printw("move(%d, %d)\n", max_y, cursor_x);
        mvprintw(
            2, 0,
            "This is a bug in the \"Kitty\" terminal emulator.\n"
            "Move left and right using arrow keys.\n"
            "Look at the bottom of the terminal. The specified cell will get skipped visually.\n"
            "Press 't' to toggle the bug.\n"
        );
        printw("THE BUG IS %s", the_bug_is_on ? "ON" : "OFF");
        mvprintw(max_y - 2, scr_width - MAGIC_OFFSET_WHERE_CURSOR_BREAKS, "|");
        mvprintw(max_y - 1, scr_width - MAGIC_OFFSET_WHERE_CURSOR_BREAKS, "V");
        if (approach == ATTRON) {
            attron(COLOR_PAIR(1));
            mvprintw(max_y, scr_width - 1, "%c", ' ');
        } else if (approach == NON_WHITESPACE) {
            mvprintw(max_y, scr_width - 1, "%c", '*');
        }
        if (!the_bug_is_on) refresh();
        if (show_getcur) {
            move(max_y, cursor_x);
            mvprintw(1, 0, "getcury() = %d, getcurx() = %d", getcury(stdscr), getcurx(stdscr));
        }
        move(max_y, cursor_x);
        refresh();
        int key = getch();
        if (key == KEY_LEFT) --cursor_x;
        else if (key == KEY_RIGHT) ++cursor_x;
        else if (key == 't') the_bug_is_on = !the_bug_is_on;
        clear();
    }
}
