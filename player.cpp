#include "player.hpp"
#include "main.hpp"
#include "config.hpp"
#include "enemy.hpp"
#include "allegroconfig.hpp"
#include <stdio.h>


extern ALLEGRO_CONFIG* iniFile;
extern Player * playerCampaign;

short Player::GetX()
{
    return x;
};

void Player::SetX(short _x)
{
    x = _x;
};

short Player::GetTempX()
{
    return tempX;
};

void Player::SetTempX( short _tempX)
{
    tempX = _tempX;
};

short Player::GetY()
{
    return y;
};

void Player::SetY( short _y)
{
    y = _y;
};

short Player::GetTempY()
{
    return tempY;
};

void Player::SetTempY( short _tempY)
{
    tempY = _tempY;
};

short Player::GetDirection()
{
    return direction;
};

void Player::SetDirection( short _direction)
{
    direction = _direction;
};

short Player::GetLife()
{
    return life;
};

void Player::SetLife(short _life)
{
    life = _life;
};

int Player::GetPoints()
{
    return points;
};

void Player::SetPoints(int _points)
{
    points = _points;
};

short Player::GetKills()
{
    return kills;
};

void Player::SetKills(short _kills)
{
    kills = _kills;
};

bool Player::GetActive()
{
    return active;
};

void Player::SetActive( bool _active)
{
    active = _active;
};

short Player::GetShoots()
{
    return shoots;
};

void Player::SetShoots( short _shoots)
{
    shoots = _shoots;
};

short Player::GetAmmoSpeed()
{
    return ammoSpeed;
};

void Player::SetAmmoSpeed( short _ammoSpeed)
{
    ammoSpeed = _ammoSpeed;
};

short Player::GetAmmoTimer()
{
    return ammoTimerDelay;
};

void Player::SetAmmoTimer( short _ammoTimerDelay)
{
    ammoTimerDelay = _ammoTimerDelay;
};

void Player::Initialize(short _x, short _y, short _life, short _shoots, short _direction, short _ammoSpeed, int _points, short _kills, short _ammoTimerDelay)
{
    x = _x/50 * 50;
    tempX = x;
    y = _y/50 * 50;
    tempY = y;
    life = _life;
    shoots = _shoots;
    direction = _direction;
    ammoSpeed = _ammoSpeed;
    points = _points;
    kills = _kills;
    active = true;
    ammoTimerDelay = _ammoTimerDelay;
};

void Player::CampaingInitialize(short _currentLevel)
{
    char levelName[15];
    sprintf(levelName, "level%i.tank", _currentLevel);

    iniFile = al_load_config_file(levelName);
    if(!iniFile)
        ShowError(levelName, 0);

    if(_currentLevel == 1)
    {
        x = atoi(al_get_config_value(iniFile, "player", "x"))/50 * 50;
        y = atoi(al_get_config_value(iniFile, "player", "y"))/50 * 50;
        life = atoi(al_get_config_value(iniFile, "player", "life"));
        shoots = atoi(al_get_config_value(iniFile, "player", "shoots"));
        direction = atoi(al_get_config_value(iniFile, "player", "direction"));
        ammoSpeed = atoi(al_get_config_value(iniFile, "player", "ammoSpeed"));
        ammoTimerDelay = atoi(al_get_config_value(iniFile, "player", "ammoTimerDelay"));
        points = 0;
        kills = 0;
    }
    else
    {
        * this = * playerCampaign;
        x = atoi(al_get_config_value(iniFile, "player", "x"))/50 * 50;
        y = atoi(al_get_config_value(iniFile, "player", "y"))/50 * 50;
        direction = atoi(al_get_config_value(iniFile, "player", "direction"));
    }
    tempX = x;
    tempY = y;
    active = true;

    al_destroy_config(iniFile);
}

void Player::Clear()
{
    x = 0;
    tempX = 0;
    y = 0;
    tempY = 0;
    life = 0;
    shoots = 1;
    direction = 0;
    ammoSpeed = 0;
    points = 0;
    kills = 0;
    active = false;
    ammoTimerDelay = 0;
    Player::ammoTimer = 0;
};

void Player::Move(short _where)
{
    switch(_where)
    {
    case 0: //prawo
    {
        direction = 0;
        tempX = x;
        x += TANK_SPEED;

        if(x > BATTLEFIELD_WIDTH)
            x = tempX;

        break;
    }
    case 1://lewo
    {
        direction = 1;
        tempX = x;
        x -= TANK_SPEED;

        if(x < 0)
            x = tempX;

        break;
    }
    case 2: //dol
    {
        direction = 2;
        tempY = y;
        y += TANK_SPEED;

        if(y > BATTLEFIELD_HEIGHT)
            y = tempY;

        break;
    }
    case 3: //gora
    {
        direction = 3;
        tempY = y;
        y -= TANK_SPEED;

        if(y < 0)
            y = tempY;

        break;
    }
    }
};

void Player::CheckColision(Wall **wall, Enemy **enemy, Bonus **bonus)
{
    for (short i=0; i < OBSTACLES ; i++)
    {
        if(wall[i] -> GetVisible())
        {
            if(x >= wall[i] -> GetX() - OBSTACLE_SIZE + MARGIN_SIZE && x <= wall[i] -> GetX() + OBSTACLE_SIZE - MARGIN_SIZE && y >= wall[i]->GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= wall[i]->GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                x = tempX;
                y = tempY;
                return; //only can collide with one thing, so if player has collision we can leave function
            }
        }
    }

    for(short g=0; g < ENEMIES; g++)
    {
        if(!enemy[g] -> GetDead())
        {
            if(x >= enemy[g] -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=enemy[g] -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= enemy[g] -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= enemy[g] -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                x = tempX;
                y = tempY;
                return;
            }
        }
    }
    for (short i=0; i < BONUSES; i++)
    {
        if(bonus[i]->GetVisible())
        {
            if(x >= bonus[i]->GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=bonus[i]->GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= bonus[i]->GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= bonus[i]->GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                RandomBonus();
                bonus[i] -> SetVisible(false);
                return;
            }
        }
    }
};
