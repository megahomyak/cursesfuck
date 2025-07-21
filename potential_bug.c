// an attempt at bug repro, DO NOT TRY you'll get nothing

#include <ncurses.h>
#include <stdbool.h>

bool wait_any_key(void) {
    refresh();
    int key = getch();
    clear();
    return key != KEY_RESIZE;
}

int main(void) {
    initscr();
    noecho();
    while (1) {
        printw("Press any key, then resize your terminal to (height=16, width=18), then press any key");
        if (wait_any_key()) break;
    }
    while (1) {
        for (int i = 0; i < 16; ++i) {
            mvprintw(i, 0, "123456789012345678");
        }
        if (wait_any_key()) break;
    }
    bool flag = 0;
    while (1) {
        mvprintw(0, 0, "Now, press any key to see the cursor jump");
        mvprintw(13, 0, "Edit sequence 1: default value ");
        mvprintw(15, 0, "Edit sequence 2:  ");
        mvprintw(16, 0, "blablablablablablablabla");
        move(15, flag ? 12 : 13);
        wait_any_key();
        flag = !flag;
    }
}
