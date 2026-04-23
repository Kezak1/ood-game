#ifndef ATTACK_TYPE
#define ATTACK_TYPE

#include "player.h"

class HeavyWeapon;
class LightWeapon;
class MagicalWeapon;

class Attack {
public:
    virtual ~Attack() = default;

    virtual int attack_pts(const Player&, const HeavyWeapon&, const Item&) const = 0;
    virtual int attack_pts(const Player&, const LightWeapon&,const Item&) const = 0;
    virtual int attack_pts(const Player&, const MagicalWeapon&, const Item&) const = 0;
    virtual int attack_pts(const Player&, const Item&, const Item&) const = 0;

    virtual int defense_pts(const Player&, const HeavyWeapon&, const Item&) const = 0;
    virtual int defense_pts(const Player&, const LightWeapon&, const Item&) const = 0;
    virtual int defense_pts(const Player&, const MagicalWeapon&, const Item&) const = 0;
    virtual int defense_pts(const Player&, const Item&, const Item&) const = 0;
};

#endif