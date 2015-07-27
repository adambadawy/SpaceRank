#pragma once


class ShipStat final
{
public:
    ShipStat();

    int getSpAvailable() const;
    int getThrust() const;
    int getHandling() const;
    int getAttackPower() const;
    int getAttackFreq() const;
    int getShield() const;
    int getHull() const;

    bool setAll
        ( int thrust
        , int handling
        , int attackPower
        , int attackFreq
        , int shield
        , int hull );

    bool changeThrust(int amount);
    bool changeHandling(int amount);
    bool changeAttackPower(int amount);
    bool changeAttackFreq(int amount);
    bool changeShield(int amount);
    bool changeHull(int amount);

private:
    bool changeStat(int &stat, int amount);

    const int MaxSp = 15;
    
    const int MinSpPerStat = 1;
    const int MaxSpPerStat = 10;

    int thrust;
    int handling;
    int attackPower;
    int attackFreq;
    int shield;
    int hull;
};
