#include "dungeon_builder.h"

#include "strong_modifier.h"
#include "unlucky_modifier.h"
#include "utils.h"
#include "great_sword.h"
#include "dagger.h"
#include "staff.h"
#include "axe.h"
#include "strange_idol.h"
#include "old_book.h"
#include "rock.h"
#include <memory>
#include <string>

DungeonBuilder::DungeonBuilder(bool start_filled) 
    : player_start_pos_r(1), player_start_pos_c(1) {
    init_board(start_filled);
    add_random_path();
    add_random_path();
    add_random_path();
    add_center_room(6, 6);
    add_random_chamber(2);
    add_random_chamber(3);
    add_random_chamber(4);
    connect_rooms();
    add_random_items(3);
    add_random_weapons(4);
    add_random_enemies();
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
        .enemies = enemies,
        .capabilities = capabilities,
    };
    return res;
}

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
    std::unique_ptr<Item> item;
    switch(next_random(1, 4)) {
        case 1: 
            item = std::make_unique<GreatSword>();
            break;
        case 2: 
            item = std::make_unique<Axe>();
            break;
        case 3:
            item = std::make_unique<Staff>();
            break;
        default: 
            item = std::make_unique<Dagger>();
            break;
    }

    int rand = next_random(1, 10);
    if(rand > 5) {
        item = std::make_unique<StrongModifier>(std::move(item));
    }
    rand = next_random(1, 10);
    if(rand > 8) {
        item = std::make_unique<UnluckyModifier>(std::move(item));
    }
    
    return item;
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
    std::vector<std::pair<int, int>> rooms_centers;
    std::vector<std::vector<bool>> vis(ROWS, std::vector<bool>(COLS, false));
    
    auto get_center_pos = [&](int start_r, int start_c) {
        std::vector<int> rs, cs;
        std::stack<std::pair<int, int>> s;
        s.push({start_r, start_c});
        vis[start_r][start_c] = true;

        while(!s.empty()) {
            auto [cur_r, cur_c] = s.top();
            s.pop();
            
            rs.push_back(cur_r);
            cs.push_back(cur_c);

            for(int i = 0; i < 4; i++) {
                int nr = cur_r + dr[i], nc = cur_c + dc[i];
                if(in_range(nr, nc) && !board[nr][nc].is_wall() && !vis[nr][nc]) {
                    s.push({nr, nc});
                    vis[nr][nc] = true;                    
                }
            }
        }
        std::sort(rs.begin(), rs.end());
        std::sort(cs.begin(), cs.end());

        return std::make_pair(rs[rs.size() / 2], cs[cs.size() / 2]);
    };

    auto carve = [&](std::pair<int, int> a, std::pair<int, int> b) {
        int start_r = a.first, start_c = a.second;
        int end_r = b.first, end_c = b.second;

        auto carve_line = [&](int r1, int c1, int r2, int c2) {
            if(r1 == r2) {
                int step = (c1 <= c2 ? 1 : -1);
                for(int c = c1; c != c2 + step; c += step) {
                    board[r1][c].set_wall(false);
                }
            } else {
                int step = (r1 <= r2 ? 1 : -1);
                for(int r = r1; r != r2 + step; r += step) {
                    board[r][c1].set_wall(false);
                }
            }
        };

        if(next_random(0, 1)) {
            carve_line(start_r, start_c, end_r, start_c);
            carve_line(end_r, start_c, end_r, end_c);
        } else {
            carve_line(start_r, start_c, start_r, end_c);
            carve_line(start_r, end_c, end_r, end_c);
        }
    };

    auto manhathan_dis = [](std::pair<int, int> a, std::pair<int, int> b) {
        return std::abs(a.first - b.first) + std::abs(a.second - b.second);
    };

    rooms_centers.push_back({player_start_pos_r, player_start_pos_c});
    for(int i = 1; i < ROWS - 1; i++) {
        for(int j = 1; j < COLS - 1; j++) {
            if(!board[i][j].is_wall() && !vis[i][j]) {
                rooms_centers.push_back(get_center_pos(i, j));
            }
        }
    }

    int size = rooms_centers.size();
    if(size <= 1) {
        return;
    }

    std::vector<bool> connected(size, false);
    connected[0] = true;

    for(int e = 0; e < size - 1; e++) {
        int best_from = -1, best_to = -1;
        int best = INT_MAX;

        for(int i = 0; i < size; i++) {
            if(!connected[i]) continue;

            for(int j = 0; j < size; j++) {
                if(connected[j]) continue;

                int d = manhathan_dis(rooms_centers[i], rooms_centers[j]);
                if(d < best) {
                    best = d;
                    best_from = i;
                    best_to = j;
                }
            }
        }

        if(best_to == -1) {
            break;
        }

        carve(rooms_centers[best_from], rooms_centers[best_to]);
        connected[best_to] = true;
    }
}

void DungeonBuilder::add_random_enemies(int count) {
    auto a = get_all_empty_pos();
    while(count-- > 0) {
        auto [r, c] = a[next_random(0, (int)a.size() - 1)];
        enemies.push_back(Enemy("Enemy" + std::to_string(count), r, c, next_random(30, 50)));
    }
    capabilities.has_enemies = true;
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
