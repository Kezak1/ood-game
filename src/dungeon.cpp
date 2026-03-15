#include "dungeon.h"

#include "utils.h"
#include "sword.h"
#include "bow.h"
#include "axe.h"
#include "strange_idol.h"
#include "old_book.h"
#include "rock.h"

bool inside(int r, int c) {
    return r > 0 && c > 0 && r < ROWS - 1 && c < COLS - 1;
}

Dungeon::Dungeon() {
    board.resize(ROWS);
    for(auto& row : board) {
        row.resize(COLS);
    }
    
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1) {
                board[i][j] = Cell(true);
            } else {
                board[i][j] = Cell(false);
            }
        }
    }

    fill_dungeon();

    add_random_path(10);
    add_random_path(15);
    add_center_room(10, 10);
    add_random_chamber(5);

    add_random_items(2);
    add_random_weapons(2);
}

std::vector<std::vector<Cell>>& Dungeon::get_board() {
    return board;
}


const std::vector<std::vector<Cell>>& Dungeon::get_board() const {
    return board;
}

void Dungeon::empty_dungeon() {
    for(int i = 1; i < ROWS - 1; i++) {
        for(int j = 1; j < COLS - 1; j++) {
            board[i][j].set_wall(false);
        }
    }
}

void Dungeon::fill_dungeon() {
    for(int i = 1; i < ROWS - 1; i++) {
        for(int j = 0; j < COLS - 1; j++) {
            board[i][j].set_wall(true);
        }
    }
}

void Dungeon::add_random_path(int len) {
    if(len <= 0) {
        return;
    }    

    int r = next_random(1, ROWS - 2);
    int c = next_random(1, COLS - 2);
    board[r][c].set_wall(false);

    while(len-- > 0) {
        std::vector<int> ok;
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if(!inside(nr, nc)) {
                continue;
            }

            if(!board[nr][nc].is_wall()) {
                continue;
            }

            int cnt_adj = 0;
            for(int j = 0; j < 4; j++) {
                int nr = r + dr[j], nc = c + dc[j];
                if(in_range(nr, nc) && !board[nr][nc].is_wall()) {
                    cnt_adj++;
                }
            }
            if(cnt_adj > 1) {
                continue;
            }

            ok.push_back(i);
        }

        if(ok.empty()) {
            break;
        }
        
        int dir = ok[next_random(0, (int)ok.size() - 1)];
        
        r += dr[dir];
        c += dc[dir];
        board[r][c].set_wall(false);
    }
}

/*
void Dungeon::add_random_paths(int l, int r) {
    if(l > r || l <= 0) {
        return;
    }

    int k = next_random(l, r);
    while(k-- > 0) {
        add_random_path(next_random(5, 15));
    }
}
*/

void Dungeon::add_random_chamber(int len) {
    int r = next_random(1, ROWS -  2 - len);
    int c = next_random(1, COLS - 2 - len);

    for(int i = r; i < r + len; i++) {
        for(int j = c; j < c + len; j++) {
            board[i][j].set_wall(false);
        }
    }
}

/*
void Dungeon::add_random_chambers(int l, int r) {
    if(l > r || l <= 0) {
        return;
    }

    int k = next_random(l, r);
    while(k-- > 0) {
        add_random_chamber(next_random(1, 10));
    }
}
*/

void Dungeon::add_center_room(int w, int h) {
    int start_r = std::max(ROWS/2 - h/2, 0);
    int start_c = std::max(COLS/2 - w/2, 0);
    
    for(int i = start_r; i < start_r + h; i++) {
        for(int j = start_c; j < start_c + h; j++) {
            board[i][j].set_wall(false);
        }
    }
}

std::unique_ptr<Item> make_random_weapon() {
    switch(next_random(1, 3)) {
        case 1: 
            return std::make_unique<Sword>(next_random(3, 9), "rusty sword");
        case 2: 
            return std::make_unique<Axe>(next_random(4, 7), "iron axe");
        default: 
            return std::make_unique<Bow>(next_random(2, 6), "short bow");
    }
}

std::unique_ptr<Item> make_random_item() {
    switch(next_random(1, 3)) {
        case 1: 
            return std::make_unique<Rock>();
        case 2: 
            return std::make_unique<OldBook>();
        default: 
            return std::make_unique<StrangeIdol>();
    }
}

void Dungeon::add_random_items(int count) {
    while(count-- > 0) {
        auto p = get_all_empty_pos();
        if(p.empty()) {
            return;
        }
        
        int idx = next_random(0, (int)p.size() - 1);
        auto [r, c] = p[idx];
        board[r][c].add_item(make_random_item());
    }
}

void Dungeon::add_random_weapons(int count) {
    while(count-- > 0) {
        auto p = get_all_empty_pos();
        if(p.empty()) {
            return;
        }

        int idx = next_random(0, (int)p.size() - 1);
        auto [r, c] = p[idx];
        board[r][c].add_item(make_random_weapon());
    }
}

void connect_rooms() {
    //TODO make sure that all empty cells are 'connected'
}

std::vector<std::pair<int, int>> Dungeon::get_all_empty_pos() {
    std::vector<std::pair<int, int>> res;
    for(int i = 1; i < ROWS - 1; i++) {
        for(int j = 1; j < COLS - 1; j++) {
            if(!board[i][j].is_wall()) {
                res.push_back({i, j});        
            }
        }
    }
    return res;
}





