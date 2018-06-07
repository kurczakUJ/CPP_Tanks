#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "wall.hpp"
#include "bonus.hpp"

class Enemy;
class Wall;
class Bonus;

class Player
{
private:
    short kills;
    int points;
    bool active;

protected:
    short shoots;
    short ammoSpeed;
    short direction;
    short x;
    short y;
    short tempX;
    short tempY;
    short life;
    short ammoTimerDelay;

public:
    Player():
        kills(0),
        points(0),
        shoots(1),
        ammoSpeed(0),
        direction(0),
        ammoTimerDelay(0)		{}

    void operator =( const Player &_playerCampaign ) //to store info for campaign
    {
        kills = _playerCampaign.kills;
        points = _playerCampaign.points;
        shoots = _playerCampaign.shoots;
        ammoSpeed = _playerCampaign.ammoSpeed;
        life = _playerCampaign.life;
        ammoTimerDelay = _playerCampaign.ammoTimerDelay;
    }

    static unsigned short ammoTimer;

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

    short GetKills();
    void SetKills( short _kills);

    int GetPoints();
    void SetPoints(int _points);

    bool GetActive();
    void SetActive( bool _active);

    short GetShoots();
    void SetShoots( short _shoots);

    short GetAmmoSpeed();
    void SetAmmoSpeed( short _ammoSpeed);

    short GetAmmoTimer();
    void SetAmmoTimer( short _ammoTimerDelay);

    void Initialize(short _x, short _y, short _life, short _shoots, short _direction, short _ammoSpeed, int _points, short _kills, short _ammoTimerDelay);
    void CampaingInitialize(short _currentLevel);
    void Move(short _where);

    void Clear();

    void CheckColision(Wall **wall, Enemy **enemy, Bonus **bonus);
};

#endif
