#include "utils.h"
#include "game.h"

int main() {
    Game g;
    g.render_state();
    while(1) {
        char k = read_key();
        if(k == 'q') {
            break;
        }
        g.move_player(k);
        clear_screen();
        g.render_state();
    }
    return 0;
}