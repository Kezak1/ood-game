#include "utils.h"
#include "game.h"

int main() {
    Game g;

    clear_screen();
    hide_cursor();
    g.render_state();

    while(1) {
        char k = read_key();
        if(k == 'q') {
            std::cout << "\033[?25h";
            break;
        }
        g.move_player(k);
        to_start_cursor();
        g.render_state();
    }

    unhide_cursor();

    return 0;
}