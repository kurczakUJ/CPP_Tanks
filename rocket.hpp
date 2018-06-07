#ifndef ROCKET_H_INCLUDED
#define ROCKET_H_INCLUDED

#include "wall.hpp"
#include "player.hpp"
#include "config.hpp"

class Rocket
{
private:
    short x;
    short y;
    short direction;
    bool team;
    bool visible;
    short speed;

public:
    Rocket():
        visible(0),
        speed(0)		{}

    static short rocketsCounter[2];

    short GetX();
    void SetX( short _x);

    short GetY();
    void SetY( short _y);

    short GetDirection();
    void SetDirection( short _direction);

    bool GetTeam();
    void SetTeam( bool _team);

    bool GetVisible();
    void SetVisible( bool _visible);

    short GetSpeed();
    void SetSpeed( short _speed);

    void RocketOff();
    void CheckColision(Rocket ** rocket, Wall ** sciany, Player *player, Enemy ** enemy, Explosion ** explosion, Bonus ** bonus);
    void Move(Rocket ** rocket, Wall ** sciany, Player *player, Enemy ** enemy, Explosion ** explosion, Bonus ** bonus);
    void Shoot(Player * player);
    void CreateSmallExplosion(Explosion ** explosion);
    void CreateBigExplosion(Explosion ** explosion, short _x, short _y);
    void HitWall(Wall ** sciany, short choice);
    void HitPlayer(Player * player);
    void HitEnemy(Enemy ** enemy, Player * player, short choice);
    void HitRocket(Rocket ** rocket, short choice);
};

short GiveRocketID(Rocket **rocket);
void ClearRocket(Rocket ** rocket);

#endif
