#include "wall.hpp"
#include "main.hpp"
#include "config.hpp"
#include "allegroconfig.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <cstdlib>
#include <cstdio>


extern ALLEGRO_CONFIG* iniFile;

short Wall::GetX()
{
    return x;
};

void Wall::SetX( short _x)
{
    x = _x;
};

short Wall::GetY()
{
    return y;
};

void Wall::SetY( short _y)
{
    y = _y;
};

bool Wall::GetDestroyable()
{
    return destroyable;
};

void Wall::SetDestroyable( bool _destroyable)
{
    destroyable = _destroyable;
};

bool Wall::GetVisible()
{
    return visible;
};

void Wall::SetVisible( bool _visible)
{
    visible = _visible;
};

bool Wall::GetBase()
{
    return base;
};

void Wall::SetBase( bool _base)
{
    base = _base;
};

short Wall::GetLife()
{
    return life;
};

void Wall::SetLife( short _life)
{
    life = _life;
};

void SetBaseID(Wall ** wall)
{
    if(Wall::baseExist == true)
    {
        for(short i=0; i < OBSTACLES; i++)
        {
            if(wall[i]->GetBase())
            {
                Wall::baseID = i;
                return;
            }
        }
    }
}

void ClearWall(Wall ** wall)
{
    for(short i=0; i < OBSTACLES; i++)
    {
        wall[i] -> SetX(0);
        wall[i] -> SetY(0);
        wall[i] -> SetDestroyable(true);
        wall[i] -> SetLife(0);
        wall[i] -> SetBase(false);
        wall[i] -> SetVisible(false);
    }

    Wall::baseExist = false;
    Wall::baseID = 0;
    Wall::respawnTimer = 0;
}

void WallCampaingInitialize(Wall **wall, Player * player, Enemy ** enemy, short currentLevel, bool respawn)
{
    char message[16];
    char levelName[15];
    short choice;

    sprintf(levelName, "level%i.tank", currentLevel);

    iniFile = al_load_config_file(levelName);
    if(!iniFile)
        ShowError(levelName, 0);

    short walls = atoi(al_get_config_value(iniFile, "options", "walls"));
    if(walls == 0)
        ShowError("error", 3);

    bool isBase = atoi(al_get_config_value(iniFile, "options", "isBase"));
    if(isBase == true)
        Wall::baseExist = true;

    for(short g = 0; g < walls; g++)
    {
        sprintf(message, "wallNR%i", g + 1);
        choice = GiveWallID(wall);
        wall[choice] -> SetDestroyable(atoi(al_get_config_value(iniFile, message, "destroyable")));
        wall[choice] -> SetLife(atoi(al_get_config_value(iniFile, message, "life")));
        wall[choice] -> SetX(atoi(al_get_config_value(iniFile, message, "x")));
        wall[choice] -> SetY(atoi(al_get_config_value(iniFile, message, "y")));
        wall[choice] -> SetBase(atoi(al_get_config_value(iniFile, message, "base")));
        if(!respawn)
            wall[choice] -> SetVisible(true);
        else
        {
            bool collision = wall[choice] -> CheckPlace(wall, player, enemy);
            if(collision)
                wall[choice] -> SetVisible(true);
        }
    }

    al_destroy_config(iniFile);
}

void Wall::Create(Wall ** wall, Player * player, Enemy ** enemy, short _x, short _y, bool _destroyable, short _life, bool _base)
{
    x = (_x/50)* 50;
    y = (_y/50)* 50;
    destroyable = _destroyable;
    life = _life;

    if(_base)
    {
        if(Wall::baseExist == false)
        {
            base = true;
            Wall::baseExist = true;
        }
    }
    else
        base = false;

    while(1)
    {
        if(this -> CheckPlace(wall,player,enemy))
            break;

        x = ((rand()%(BATTLEFIELD_WIDTH - 50))/50)* 50;
        y = ((rand()%(BATTLEFIELD_HEIGHT - 50))/50)* 50;
    }

    visible = true;
};

bool Wall::CheckPlace(Wall **wall, Player * player, Enemy **enemy)
{
    for (short i=0; i<OBSTACLES ; i++)
    {
        if(wall[i]->GetVisible() && this != wall[i])
        {
            if(x > wall[i] -> GetX() - OBSTACLE_SIZE && x < wall[i] -> GetX() + OBSTACLE_SIZE )
                if(y + OBSTACLE_SIZE > wall[i] -> GetY() && y < wall[i] -> GetY() + OBSTACLE_SIZE )
                    return false;
        }
    }

    if(player->GetActive())
    {
        if(x > player -> GetX() - OBSTACLE_SIZE && x < player -> GetX() + TANK_SIZE)
            if(y + TANK_SIZE > player -> GetY() && y < player -> GetY() + TANK_SIZE )
                return false;
    }


    for(short j=0; j<ENEMIES; j++)
    {
        if(!enemy[j] -> GetDead())
        {
            if(x > enemy[j] -> GetX() - OBSTACLE_SIZE && x < enemy[j] -> GetX() + TANK_SIZE)
                if(y + TANK_SIZE > enemy[j] -> GetY() && y < enemy[j] -> GetY() + TANK_SIZE)
                    return false;
        }
    }

    return true;
};

short GiveWallID(Wall **wall)
{
    for(short i=0; i<OBSTACLES; i++)
    {
        if(!wall[i]->GetVisible())
            return i;
    }

    return 0;
};

short CheckExistsWalls(Wall **wall)
{
    short temp=0;
    for(short i=0; i<OBSTACLES; i++)
    {
        if(wall[i]->GetVisible())
            temp++;
    }

    return temp;
}

void SetImmortallWallsVisible(Wall **wall)
{
    for (short i=0; i<OBSTACLES ; i++)
    {
        if(wall[i]->GetVisible() && wall[i]->GetDestroyable() == false)
        {
            for(short j = wall[i] -> GetY() ; j <= wall[i] -> GetY() + OBSTACLE_SIZE; j++)
            {
                for(short k = wall[i] -> GetX() ; k <= wall[i] -> GetX() + OBSTACLE_SIZE; k++)
                {
                    if(k < 0 || j < 0)
                        continue;

                    Enemy::isPlayer[k][j] = 4;
                }
            }
        }
    }
}
