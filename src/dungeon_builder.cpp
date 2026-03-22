#include "dungeon_builder.h"

#include "utils.h"
#include "sword.h"
#include "bow.h"
#include "axe.h"
#include "strange_idol.h"
#include "old_book.h"
#include "rock.h"

// #include <queue>
// #include <limits>

DungeonBuilder::DungeonBuilder(int r, int c, bool start_filled) : player_start_pos_r(r), player_start_pos_c(c) {
    init_board(start_filled);
    add_random_path();
    add_center_room(6, 6);
    connect_rooms();
    add_random_items(2);
    add_random_weapons(2);
}

void DungeonBuilder::init_board(bool start_filled) {
    board.resize(ROWS);
    for(auto& row : board) {
        row.resize(COLS);
    }
    
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1 || start_filled) {
                board[i][j] = Cell(true);
            } else {
                board[i][j] = Cell(false);
            }
        }
    }
}


BuildResult DungeonBuilder::build() {
    board[player_start_pos_r][player_start_pos_c].set_wall(false);
    BuildResult res {
        .board = std::move(board),
        .capabilities = capabilities
    };
    return res;
}

/*
void DungeonBuilder::empty_dungeon() {
    for(int i = 1; i < ROWS - 1; i++) {
        for(int j = 1; j < COLS - 1; j++) {
            board[i][j].set_wall(false);
        }
    }
}

void DungeonBuilder::fill_dungeon() {
    for(int i = 1; i < ROWS - 1; i++) {
        for(int j = 0; j < COLS - 1; j++) {
            board[i][j].set_wall(true);
        }
    }
}
*/

bool inside(int r, int c) {
    return r > 0 && c > 0 && r < ROWS - 1 && c < COLS - 1;
}

void DungeonBuilder::add_random_path() {
    capabilities.can_move = true;

    int len = next_random(10,20);

    std::vector<std::vector<char>> f(ROWS, std::vector<char>(COLS, '-'));
    std::vector<std::pair<int, int>> pos;
    std::vector<int> dirs;

    int r = next_random(1, ROWS - 2);
    int c = next_random(1, COLS - 2);

    pos.push_back({r, c});
    dirs.push_back(-1);
    f[r][c] = '*';
    
    while(len-- > 0) {
        std::vector<int> ok;

        for(int i = 0; i < 4; i++) {
            int nr = r + 2*dr[i], nc = c + 2*dc[i];
            if(!inside(nr, nc)) {
                continue;
            }

            if(f[nr][nc] != '-') {
                continue;
            }

            ok.push_back(i);
        }

        if(ok.empty()) {
            break;
        }
        
        int dir = ok[next_random(0, (int)ok.size() - 1)];
        if(dirs[0] == -1) {
            dirs[0] = dir;
        }
            
        for(int k = 0; k < 2; k++) {
            r += dr[dir];
            c += dc[dir];
            f[r][c] = '*';
            pos.push_back({r, c});
            dirs.push_back(dir);
        }
    }

    auto make_corner = [&f](int r, int c) {
        for(std::pair<int, int> p : {std::make_pair(0, 1), {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}}) {
            int nr = r + p.first, nc = c + p.second;
            if(inside(nr, nc) && f[nr][nc] == '-') {
                f[nr][nc] = '#';
            } 
        }
    };

    auto make_opening = [&f](int r, int c, int dir) {
        if(dir < 2) {
            if(inside(r + 1, c)) f[r + 1][c] = '#';
            if(inside(r - 1, c)) f[r - 1][c] = '#';
        } else {
            if(inside(r, c + 1)) f[r][c + 1] = '#';
            if(inside(r, c - 1)) f[r][c - 1] = '#';
        }
    };

    int size = pos.size();

    if(size >= 2) {
        make_opening(pos[0].first, pos[0].second, dirs[0]);
        for(int i = 1; i < size - 1; i++) {
            int r = pos[i].first, c = pos[i].second;
            make_corner(r, c);
        }
        make_opening(pos[size - 1].first, pos[size - 1].second, dirs[size - 1]);
    }

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            char& c = f[i][j];
            if(c == '#') {
                board[i][j].set_wall(true);
            } else if(c == '*') {
                board[i][j].set_wall(false);
            }
        }
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

void DungeonBuilder::add_random_chamber(int len) {
    capabilities.can_move = true;

    len += 2;
    int r = next_random(1, ROWS -  2 - len);
    int c = next_random(1, COLS - 2 - len);

    for(int i = r; i < r + len; i++) {
        for(int j = c; j < c + len; j++) {
            if(i == r || j == c || i == r + len - 1 || j == c + len - 1) {
                board[i][j].set_wall(true);
            } else {
                board[i][j].set_wall(false);
            }
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

void DungeonBuilder::add_center_room(int w, int h) {
    capabilities.can_move = true;
    w += 2, h += 2;
    int start_r = std::max(ROWS/2 - h/2, 0), start_c = std::max(COLS/2 - w/2, 0);
    int end_r = std::min(start_r + h, ROWS), end_c = std::min(start_c + w, COLS);
    for(int i = start_r; i < end_r; i++) {
        for(int j = start_c; j < end_c; j++) {
            if(i == start_r || i == end_r - 1 || j == start_c || j == end_c - 1) {
                board[i][j].set_wall(true);
            } else {
                board[i][j].set_wall(false);
            }
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

void DungeonBuilder::add_random_items(int count) {
    if(count > 0) capabilities.has_items = true;
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

void DungeonBuilder::add_random_weapons(int count) {
    capabilities.has_weapons = true;
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

void DungeonBuilder::connect_rooms() {
   //TO DO connect empty cells such way thats its connected graph
}

std::vector<std::pair<int, int>> DungeonBuilder::get_all_empty_pos() {
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
