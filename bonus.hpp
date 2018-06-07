#ifndef BONUSKI_H_INCLUDED
#define BONUSKI_H_INCLUDED

#include "explosion.hpp"

class Enemy;

class Bonus : public Wall
{
public:
    short GetX();
    void SetX( short _x);

    short GetY();
    void SetY( short _y);

    bool GetVisible();
    void SetVisible( bool _visible);
};

short GiveBonusID(Bonus ** bonus);
void Airstrike(Enemy ** enemy, Explosion ** explosion, Bonus ** bonus, Player *player);
void ClearBonus(Bonus ** bonus);

#endif
