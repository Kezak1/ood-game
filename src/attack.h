#ifndef ATTACK_TYPE
#define ATTACK_TYPE

#include "player.h"

class HeavyWeapon;
class LightWeapon;
class MagicalWeapon;

class Attack {
public:
    virtual ~Attack() = default;

    virtual int visit_attack(const Player&, const HeavyWeapon&, const Item&) const = 0;
    virtual int visit_attack(const Player&, const LightWeapon&,const Item&) const = 0;
    virtual int visit_attack(const Player&, const MagicalWeapon&, const Item&) const = 0;
    virtual int visit_attack(const Player&, const Item&, const Item&) const = 0;

    virtual int visit_defense(const Player&, const HeavyWeapon&, const Item&) const = 0;
    virtual int visit_defense(const Player&, const LightWeapon&, const Item&) const = 0;
    virtual int visit_defense(const Player&, const MagicalWeapon&, const Item&) const = 0;
    virtual int visit_defense(const Player&, const Item&, const Item&) const = 0;
};

#endif