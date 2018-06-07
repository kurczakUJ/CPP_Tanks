#include "explosion.hpp"
#include "config.hpp"

short Explosion::GetX()
{
    return x;
};

void Explosion::SetX( short _x)
{
    x = _x;
};

short Explosion::GetY()
{
    return y;
};

void Explosion::SetY( short _y)
{
    y = _y;
};

short Explosion::GetAnimationHeight()
{
    return animationHeight;
};

void Explosion::SetAnimationHeight( short _animationHeight)
{
    animationHeight = _animationHeight;
};

short Explosion::GetAnimationWidth()
{
    return animationWidth;
};

void Explosion::SetAnimationWidth( short _animationWidth)
{
    animationWidth = _animationWidth;
};

bool Explosion::GetVisible()
{
    return visible;
};

void Explosion::SetVisible( bool _visible)
{
    visible = _visible;
};

short Explosion::GetLife()
{
    return life;
};

void Explosion::SetLife( short _life)
{
    life = _life;
};

bool Explosion::GetSmall()
{
    return smallExplosion;
};

void Explosion::SetSmall( bool _smallExplosion)
{
    smallExplosion = _smallExplosion;
};

void Explosion::CreateExplosion()
{
    if(visible)
    {
        life --;

        if(life == 0)
            visible = false;
    }
};

short GiveExplosionID(Explosion **explosion)
{
    for(short i=0; i<EXPLOSIONS; i++)
    {
        if(!explosion[i] -> GetVisible())
            return i;
    }
    return 0;
};

void ClearExplosion(Explosion **explosion)
{
    for(short i=0; i<EXPLOSIONS; i++)
    {
        explosion[i] -> SetX(0);
        explosion[i] -> SetY(0);
        explosion[i] -> SetVisible(false);
        explosion[i] -> SetAnimationHeight(0);
        explosion[i] -> SetAnimationWidth(0);
        explosion[i] -> SetLife(0);
        explosion[i] -> SetSmall(false);
    }
}
