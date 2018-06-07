#ifndef EXPLODE_H_INCLUDED
#define EXPLODE_H_INCLUDED

#include "wall.hpp"

class Explosion : public Wall
{
private:
    bool smallExplosion;
    short animationHeight;
    short animationWidth;

public:
    Explosion():
        smallExplosion(false),
        animationHeight(0),
        animationWidth(0)		{}

    short GetX();
    void SetX( short _x);

    short GetY();
    void SetY( short _y);

    short GetLife();
    void SetLife( short _life);

    short GetAnimationHeight();
    void SetAnimationHeight( short _animationHeight);

    short GetAnimationWidth();
    void SetAnimationWidth( short _animationWidth);

    bool GetVisible();
    void SetVisible( bool _visible);

    bool GetSmall();
    void SetSmall( bool _smallExplosion);

    void CreateExplosion();

};

short GiveExplosionID(Explosion **explosion);
void ClearExplosion(Explosion **explosion);

#endif
