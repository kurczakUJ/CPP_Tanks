#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "player.hpp"
#include "rocket.hpp"
#include "config.hpp"
#include <cstring>
#include <stdint.h>

class Enemy : public Player
{
private:
    bool dead;
    bool colision;
    short tempDirection;
    short directionCounter;
    short destinationX;
    short destinationY;
    short tempDestinationX;
    short tempDestinationY;
    bool canShoot;
    bool tarGetAhead;
    short ammoTimer;
    short ammoDelay;
    short respawnDelayTimer;
    short difficulty; // 0 - Normal 1 - Mid 2- Fast 3-heavy
    bool stop;
    short wallID;
    bool wallAtPath;
    bool firstmovement;
    bool attack;
    short id;

public:
    Enemy(short _id):
        dead(1),
        directionCounter(0),
        destinationX(0),
        destinationY(0),
        tempDestinationX(0),
        tempDestinationY(0),
        canShoot(true),
        tarGetAhead(false),
        ammoTimer(0),
        ammoDelay(0),
        respawnDelayTimer(0),
        difficulty(0),
        stop(false),
        wallID(0),
        wallAtPath(false),
        firstmovement(false),
        attack(false)
    {
        id = _id;
    }

    static uint8_t isPlayer[REAL_BATTLEFIELD_WIDTH+TANK_SIZE+1][REAL_BATTLEFIELD_HEIGHT+TANK_SIZE+1];
    static bool hasPlayer ;
    static bool hasBase ;
    static short baseCoord[2];
    static short playerTimer;
    static short playerDirection;
    static bool attackBase[3];
    static short lostPlayerTimer;

    short GetX();
    void SetX(short _x);

    short GetY();
    void SetY( short _y);

    short GetTempX();
    void SetTempX( short _tempX);

    short GetTempY();
    void SetTempY( short _tempY);

    short GetDirection();
    void SetDirection( short _direction);

    short GetLife();
    void SetLife( short _life);

    bool GetDead();
    void SetDead( bool _dead);

    short GetWallID();
    void SetWallID( short _wallID);

    bool GetFirstmovement();
    void SetFirstmovement( bool _firstmovement);

    bool GetColision();
    void SetColision( bool _colision);

    bool GetCanShoot();
    void SetCanShoot( bool _canShoot);

    short GetAmmoSpeed();
    void SetAmmoSpeed( short _ammoSpeed);

    short GetTempDirection();
    void SetTempDirection( short _tempDirection);

    short GetDirectionCounter();
    void SetDirectionCounter( short _directionCounter);

    short GetDestinationX();
    void SetDestinationX(short _destinationX);

    short GetDestinationY();
    void SetDestinationY( short _destinationY);

    short GetTempDestinationX();
    void SetTempDestinationX(short _tempDestinationX);

    short GetTempDestinationY();
    void SetTempDestinationY( short _tempDestinationY);

    bool GetTarGetAhead();
    void SetTarGetAhead( bool _tarGetAhead);

    short GetAmmoTimer();
    void SetAmmoTimer( short _ammoTimer);

    short GetAmmoDelay();
    void SetAmmoDelay( short _ammoDelay);

    short GetRespawnDelayTimer();
    void SetRespawnDelayTimer( short _respawnDelayTimer);

    short GetDifficulty();
    void SetDifficulty( short _difficulty);

    bool GetStop();
    void SetStop( bool _stop);

    bool GetWallAtPath();
    void SetWallAtPath( bool _wallAtPath);

    bool GetAttack();
    void SetAttack( bool _attack);

    void SetPlayerCoord(Enemy **enemy, Player * player);
    void CheckPlace(Wall **wall, Player * player, Enemy **enemy);
    short CheckCollision(Wall **wall, Player * player, Enemy **enemy, Bonus **bonus);
    void Spawn(short _x, short _y, short _life, short _ammoSpeed, short _direction, short _ammoDelay, short _difficulty, Wall **wall, Player * player, Enemy **enemy);
    bool CheckAimWall(Wall **wall, Enemy ** enemy);
    bool CheckAimImmortallWall(Wall **wall, short _x, short _y);
    bool CheckAimPlayer(Player *player, Enemy ** enemy, Wall ** wall);
    bool CheckAimBase(Wall **wall, short id, Enemy ** enemy);
    bool CheckAimEnemy(Enemy **enemy, short _x, short _y);
    bool SearchForDirection();
    void CheckForBase(Wall ** wall, Enemy ** enemy);
    void CheckForPlayer(Player *player, Enemy **enemy);
    bool CheckDirection(short direction, Wall ** wall, Enemy ** enemy, Player *player, short moves);
    void Shoot(Rocket ** rocket);
    void CheckNearbyArea(Wall ** wall, Enemy ** enemy, Player * player);
    bool CheckPlayerFuture(short direction, Player *player, short moves);
    void CheckDestination(Wall ** wall);
    void FightCoord(Player *player, Wall ** wall, Enemy **enemy);
    short EnemyPilot(Enemy **enemy, Wall **wall, Player *player, bool fight);
    void MoveCorrection(Wall **wall, Player *player, Enemy **enemy, Bonus **bonus);
    void MoveAI(Wall **wall, Player *player, Enemy **enemy, Bonus **bonus);
    void EnemyAI(Wall **wall, Enemy **enemy, Player *player, Bonus **bonus, Rocket **rocket);
};

short GiveEnemyID(Enemy **enemy);
void ClearPlayerArray(Wall ** wall);
void ClearWallArray();
void ClearEnemy(Enemy **enemy);
short CheckEnemyAlive(Enemy **enemy);
void SetBaseCoord(Enemy ** enemy, Wall **wall, short choice);
void EnemycampaingInitialize(Enemy ** enemy, short currentLevel, Wall **wall, Player *player);
void EnemyCampaignDrop(Enemy ** enemy, short currentLevel, Wall **wall, Player *player);
void SetTarGet(Enemy **enemy, Player *player);

#endif
