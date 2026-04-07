#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
    int r, c;
    int hp;
public:
    Entity(int r, int c, int hp = 100);
    
    const int& get_r() const;
    void set_r(int row);
    const int& get_c() const;
    void set_c(int col);

    const int& get_hp() const;
    bool is_dead() const;
};

#endif