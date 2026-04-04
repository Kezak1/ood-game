#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    int r, c;
    int hp = 100;
public:
    Entity(int r, int c);
    
    const int& get_r() const;
    void set_r(int row);
    const int& get_c() const;
    void set_c(int col);

    const int& get_hp() const;
};

#endif