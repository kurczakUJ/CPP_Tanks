#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include <stdint.h>

class Player;
class Enemy;

class Wall
{
private:
    bool destroyable;
    bool base;

protected:
    short x;
    short y;
    short life;
    bool visible;

public:

    Wall():
        base(false) {}

    static short respawnTimer;
    static short baseID;
    static bool baseExist;

    short GetX();
    void SetX( short _x);

    short GetY();
    void SetY( short _y);

    short GetLife();
    void SetLife( short _life);

    bool GetDestroyable();
    void SetDestroyable( bool _destroyable);

    bool GetVisible();
    void SetVisible( bool _visible);

    bool GetBase();
    void SetBase( bool _base);

    bool CheckPlace(Wall **wall, Player * player, Enemy **enemy);
    void Create(Wall ** wall, Player * player, Enemy ** enemy, short _x, short _y, bool _destroyable, short _life, bool _base);

};

short GiveWallID(Wall **wall);
void SetBaseID(Wall ** wall);
void ClearWall(Wall ** wall);
short CheckExistsWalls(Wall **wall);
void WallCampaingInitialize(Wall **wall, Player * player, Enemy ** enemy, short currentLevel, bool respawn);
void SetImmortallWallsVisible(Wall **wall);

#endif
