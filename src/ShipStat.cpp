#include "ShipStat.h"


ShipStat::ShipStat()
    : thrust(MinSpPerStat)
    , handling(MinSpPerStat)
    , attackPower(MinSpPerStat)
    , attackFreq(MinSpPerStat)
    , shield(MinSpPerStat)
    , hull(MinSpPerStat)
{}


int ShipStat::getSpAvailable() const
{
    int allocatedSp =
        thrust + handling + attackPower + attackFreq + shield + hull;
    return MaxSp - allocatedSp;
}


int ShipStat::getThrust() const { return thrust; }
int ShipStat::getHandling() const { return handling; }
int ShipStat::getAttackPower() const { return attackPower; }
int ShipStat::getAttackFreq() const { return attackFreq; }
int ShipStat::getShield() const { return shield; }
int ShipStat::getHull() const { return hull; }


bool ShipStat::setAll
    ( int thrust
    , int handling
    , int attackPower
    , int attackFreq
    , int shield
    , int hull )
{
    int sum = thrust + handling + attackPower + attackFreq + shield + hull;
    if (sum > MaxSp)
        return false;
    if (thrust < MinSpPerStat || thrust > MaxSpPerStat)
        return false;
    if (handling < MinSpPerStat || thrust > MaxSpPerStat)
        return false;
    if (attackPower < MinSpPerStat || thrust > MaxSpPerStat)
        return false;
    if (attackFreq < MinSpPerStat || thrust > MaxSpPerStat)
        return false;
    if (shield < MinSpPerStat || thrust > MaxSpPerStat)
        return false;
    if (hull < MinSpPerStat || thrust > MaxSpPerStat)
        return false;

    this->thrust = thrust;
    this->handling = handling;
    this->attackPower = attackPower;
    this->attackFreq = attackFreq;
    this->shield = shield;
    this->hull = hull;
    return true;
}


bool ShipStat::changeThrust(int amount) { return changeStat(thrust, amount); }
bool ShipStat::changeHandling(int amount) { return changeStat(handling, amount); }
bool ShipStat::changeAttackPower(int amount) { return changeStat(attackPower, amount); }
bool ShipStat::changeAttackFreq(int amount) { return changeStat(attackFreq, amount); }
bool ShipStat::changeShield(int amount) { return changeStat(shield, amount); }
bool ShipStat::changeHull(int amount) { return changeStat(hull, amount); }

bool ShipStat::changeStat(int &stat, int amount)
{
    if (amount > getSpAvailable())
        return false;
    int next = stat + amount;
    if (next > MaxSpPerStat || next < MinSpPerStat)
        return false;
    stat = next;
    return true;
}
