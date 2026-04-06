#ifndef ATTACK_TYPE
#define ATTACK_TYPE

#include "player.h"

inline constexpr double DEF_MAX = 40.0;

class HeavyWeapon;
class LightWeapon;
class MagicalWeapon;

class Attack {
public:
    virtual ~Attack() = default;

    virtual int attack_dmg(const Player&, const HeavyWeapon&) const = 0;
    virtual int attack_dmg(const Player&, const LightWeapon&) const = 0;
    virtual int attack_dmg(const Player&, const MagicalWeapon&) const = 0;
    virtual int attack_dmg(const Player&, const Item&) const = 0;

    virtual double defense_ratio(const Player&, const HeavyWeapon&) const = 0;
    virtual double defense_ratio(const Player&, const LightWeapon&) const = 0;
    virtual double defense_ratio(const Player&, const MagicalWeapon&) const = 0;
    virtual double defense_ratio(const Player&, const Item&) const = 0;
};

#endif