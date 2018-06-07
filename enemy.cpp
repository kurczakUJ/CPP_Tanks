#include "enemy.hpp"
#include "config.hpp"
#include "allegroconfig.hpp"
#include "main.hpp"
#include "aStar.hpp"
#include <cstdlib>
#include <cstdio>
#include <string>

extern ALLEGRO_CONFIG* iniFile;
extern ALLEGRO_SAMPLE *sound[SOUNDS];
extern short enemiesAtOnce;
extern short enemies;
extern short enemiesKilled;
extern bool start;
extern bool gameover;
extern unsigned short gameMode;

short Enemy::GetX()
{
    return x;
};

void Enemy::SetX(short _x)
{
    x = _x;
};

short Enemy::GetTempX()
{
    return tempX;
};

void Enemy::SetTempX( short _tempX)
{
    tempX = _tempX;
};

short Enemy::GetY()
{
    return y;
};

void Enemy::SetY( short _Y)
{
    y = _Y;
};

short Enemy::GetTempY()
{
    return tempY;
};

void Enemy::SetTempY( short _tempY)
{
    tempY = _tempY;
};

bool Enemy::GetColision()
{
    return colision;
};

void Enemy::SetColision( bool _colision)
{
    colision = _colision;
};

short Enemy::GetDirection()
{
    return direction;
};

void Enemy::SetDirection( short _direction)
{
    direction = _direction;
};

short Enemy::GetLife()
{
    return life;
};

void Enemy::SetLife(short _life)
{
    life = _life;
};

bool Enemy::GetDead()
{
    return dead;
};

void Enemy::SetDead( bool _dead)
{
    dead = _dead;
};

bool Enemy::GetCanShoot()
{
    return canShoot;
};

void Enemy::SetCanShoot( bool _canShoot)
{
    canShoot = _canShoot;
};

short Enemy::GetAmmoSpeed()
{
    return ammoSpeed;
};

void Enemy::SetAmmoSpeed( short _ammoSpeed)
{
    ammoSpeed = _ammoSpeed;
};

short Enemy::GetTempDirection()
{
    return tempDirection;
};

void Enemy::SetTempDirection( short _tempDirection)
{
    tempDirection = _tempDirection;
};

short Enemy::GetDirectionCounter()
{
    return directionCounter;
};

void Enemy::SetDirectionCounter( short _directionCounter)
{
    directionCounter = _directionCounter;
};

short Enemy::GetDestinationX()
{
    return destinationX;
};

void Enemy::SetDestinationX(short _destinationX)
{
    destinationX = _destinationX;
};

short Enemy::GetDestinationY()
{
    return destinationY;
};

void Enemy::SetDestinationY(short _destinationY)
{
    destinationY = _destinationY;
};

bool Enemy::GetTarGetAhead()
{
    return tarGetAhead;
};

void Enemy::SetTarGetAhead(bool _tarGetAhead)
{
    tarGetAhead = _tarGetAhead;
};

short Enemy::GetAmmoTimer()
{
    return ammoTimer;
};

void Enemy::SetAmmoTimer( short _ammoTimer)
{
    ammoTimer = _ammoTimer;
};

short Enemy::GetAmmoDelay()
{
    return ammoDelay;
};

void Enemy::SetAmmoDelay( short _ammoDelay)
{
    ammoDelay = _ammoDelay;
};

short Enemy::GetRespawnDelayTimer()
{
    return respawnDelayTimer;
};

void Enemy::SetRespawnDelayTimer( short _respawnDelayTimer)
{
    respawnDelayTimer = _respawnDelayTimer;
};

short Enemy::GetDifficulty()
{
    return difficulty;
};

void Enemy::SetDifficulty( short _difficulty)
{
    difficulty = _difficulty;
};

bool Enemy::GetStop()
{
    return stop;
}

void Enemy::SetStop( bool _stop)
{
    stop = _stop;
}

short Enemy::GetTempDestinationX()
{
    return tempDestinationX;
}

void Enemy::SetTempDestinationX(short _tempDestinationX)
{
    tempDestinationX = _tempDestinationX;
}

short Enemy::GetTempDestinationY()
{
    return tempDestinationY;
}

void Enemy::SetTempDestinationY( short _tempDestinationY)
{
    tempDestinationY = _tempDestinationY;
}

short Enemy::GetWallID()
{
    return wallID;
}

void Enemy::SetWallID( short _wallID)
{
    wallID = _wallID;
}

bool Enemy::GetWallAtPath()
{
    return wallAtPath;
}

void Enemy::SetWallAtPath( bool _wallAtPath)
{
    wallAtPath = _wallAtPath;
}

bool Enemy::GetFirstmovement()
{
    return firstmovement;
}

void Enemy::SetFirstmovement( bool _firstmovement)
{
    firstmovement = _firstmovement;
}

bool Enemy::GetAttack()
{
    return attack;
}

void Enemy::SetAttack( bool _attack)
{
    attack = _attack;
}

short GiveEnemyID(Enemy **enemy)
{
    for(short i=0; i<  ENEMIES; i++)
    {
        if(enemy[i] -> GetDead())
            return i;
    }

    return 0;
};

void Enemy::SetPlayerCoord(Enemy **enemy, Player * player)
{
    short playerX = player -> GetX();
    short playerY = player -> GetY();

    Enemy::playerDirection = player -> GetDirection();

    for(short g = 0; g < ENEMIES; g++)
    {
        if(!enemy[g] -> GetDead())
        {
            if(!enemy[g] -> GetAttack() || (Enemy::attackBase[g] == 0 && Wall::baseExist == true))
            {
                enemy[g] -> SetDestinationX(playerX);
                enemy[g] -> SetDestinationY(playerY);
            }
        }
    }
}

void SetBaseCoord(Enemy ** enemy, Wall **wall, short choice)
{
    short baseX = wall[Wall::baseID] -> GetX();
    short baseY = wall[Wall::baseID] -> GetY();

    Enemy::baseCoord[0] = baseX;
    Enemy::baseCoord[1] = baseY;

    for(short g = 0; g < ENEMIES; g++)
    {
        if(!enemy[g] -> GetDead())
        {
            if(!enemy[g] -> GetAttack() && Enemy::attackBase[g] == 1 && Wall::baseExist == true)
            {
                enemy[choice] -> SetDestinationX(baseX);
                enemy[choice] -> SetDestinationY(baseY);
            }
        }
    }
}

void ClearEnemy(Enemy **enemy)
{
    for(short g = 0; g < ENEMIES; g++)
    {
        enemy[g] -> SetTempX(0);
        enemy[g] -> SetTempY(0);
        enemy[g] -> SetDirection(0);
        enemy[g] -> SetLife(0);
        enemy[g] -> SetColision(false);
        enemy[g] -> SetX(0);
        enemy[g] -> SetY(0);
        enemy[g] -> SetAmmoSpeed(0);
        enemy[g] -> SetDead(true);
        enemy[g] -> SetAmmoTimer(0);
        enemy[g] -> SetAmmoDelay(0);
        enemy[g] -> SetRespawnDelayTimer(0);
        enemy[g] -> SetDifficulty(0);
        enemy[g] -> SetTempDirection(0);
        enemy[g] -> SetDirectionCounter(0);
        enemy[g] -> SetCanShoot(true);
        enemy[g] -> SetTarGetAhead(false);
        enemy[g] -> SetStop(false);
        enemy[g] -> SetTempDestinationY(0);
        enemy[g] -> SetTempDestinationX(0);
        enemy[g] -> SetWallAtPath(false);
        enemy[g] -> SetFirstmovement(false);
        enemy[g] -> SetAttack(false);
        enemy[g] -> SetDestinationX(0);
        enemy[g] -> SetDestinationY(0);
        enemy[g] -> SetWallID(0);
    }

    Enemy::playerTimer = 0;
    Enemy::hasPlayer = false;
    Enemy::hasBase = false;
    Enemy::baseCoord[0] = 0;
    Enemy::baseCoord[1] = 0;
}

void ClearPlayerArray(Wall ** wall)
{
    for(short i=0; i< REAL_BATTLEFIELD_WIDTH; i++)
        for(short j=0; j< REAL_BATTLEFIELD_HEIGHT; j++)
        {
            Enemy::isPlayer[i][j] = 0;
        }

    SetImmortallWallsVisible(wall);
}

void EnemycampaingInitialize(Enemy ** enemy, short currentLevel, Wall **wall, Player *player)
{
    char message[16];
    char levelName[15];
    short choice;

    sprintf(levelName, "level%i.tank", currentLevel);

    iniFile = al_load_config_file(levelName);
    if(!iniFile)
        ShowError(levelName, 0);

    enemies = atoi(al_get_config_value(iniFile, "options", "enemies"));
    if(enemies == 0)
        ShowError("error", 3);

    enemiesAtOnce = atoi(al_get_config_value(iniFile, "options", "enemiesAtOnce"));
    if(enemiesAtOnce == 0)
        ShowError("error", 3);

    for(short g = 1; g <= enemiesAtOnce; g++)
    {
        sprintf(message, "enemyNR%i", g);
        choice = GiveEnemyID(enemy);
        enemy[choice] -> SetDirection(atoi(al_get_config_value(iniFile, message, "direction")));
        enemy[choice] -> SetLife(atoi(al_get_config_value(iniFile, message, "life")));
        enemy[choice] -> SetColision(true);
        enemy[choice] -> SetStop(false);
        enemy[choice] -> SetX(atoi(al_get_config_value(iniFile, message, "x"))/TANK_SIZE * TANK_SIZE);
        enemy[choice] -> SetY(atoi(al_get_config_value(iniFile, message, "y"))/TANK_SIZE * TANK_SIZE);
        enemy[choice] -> SetAmmoSpeed(atoi(al_get_config_value(iniFile, message, "ammoSpeed")));
        enemy[choice] -> SetAmmoDelay(atoi(al_get_config_value(iniFile, message, "ammoDelay")));
        enemy[choice] -> SetDifficulty(atoi(al_get_config_value(iniFile, message, "difficulty")));
        enemy[choice] -> SetTempDestinationY(0);
        enemy[choice] -> SetTempDestinationX(0);
        enemy[choice] -> SetWallAtPath(false);
        enemy[choice] -> SetFirstmovement(false);
        enemy[choice] -> SetAmmoTimer(0);
        enemy[choice] -> SetTempDirection(0);
        enemy[choice] -> SetDirectionCounter(0);
        enemy[choice] -> SetCanShoot(true);
        enemy[choice] -> SetTarGetAhead(false);
        enemy[choice] -> SetAttack(false);
        enemy[choice] -> SetDestinationX(0);
        enemy[choice] -> SetDestinationY(0);
        enemy[choice] -> SetWallID(0);
        enemy[choice] -> SetRespawnDelayTimer(0);

        while(enemy[choice] -> GetColision())
        {
            enemy[choice] -> CheckPlace(wall, player, enemy);

            if(!enemy[choice] -> GetColision())
                break;

            enemy[choice] -> SetX(rand()%(BATTLEFIELD_WIDTH)/TANK_SIZE * TANK_SIZE);
            enemy[choice] -> SetY(rand()%(BATTLEFIELD_HEIGHT)/TANK_SIZE * TANK_SIZE);
        }

        enemy[choice] -> SetTempX(enemy[choice] -> GetX());
        enemy[choice] -> SetTempY(enemy[choice] -> GetY());
        enemy[choice] -> SetDead(false);
    }

    SetTarGet(enemy, player);
    al_destroy_config(iniFile);
}

void EnemyCampaignDrop(Enemy ** enemy, short currentLevel, Wall **wall, Player *player)
{
    char message[16];
    char levelName[15];
    short choice;

    sprintf(levelName, "level%i.tank", currentLevel);

    iniFile = al_load_config_file(levelName);
    if(!iniFile)
        ShowError(levelName, 0);

    for(short g = enemiesKilled + CheckEnemyAlive(enemy) ; g < enemiesAtOnce + enemiesKilled; g++)
    {
        if( enemiesKilled + CheckEnemyAlive(enemy) < enemies )
        {
            sprintf(message, "enemyNR%i", g + 1);
            choice = GiveEnemyID(enemy);
            enemy[choice] -> SetDirection(atoi(al_get_config_value(iniFile, message, "direction")));
            enemy[choice] -> SetLife(atoi(al_get_config_value(iniFile, message, "life")));
            enemy[choice] -> SetColision(true);
            enemy[choice] -> SetStop(false);
            enemy[choice] -> SetX(atoi(al_get_config_value(iniFile, message, "x"))/TANK_SIZE * TANK_SIZE);
            enemy[choice] -> SetY(atoi(al_get_config_value(iniFile, message, "y"))/TANK_SIZE * TANK_SIZE);
            enemy[choice] -> SetAmmoSpeed(atoi(al_get_config_value(iniFile, message, "ammoSpeed")));
            enemy[choice] -> SetAmmoDelay(atoi(al_get_config_value(iniFile, message, "ammoDelay")));
            enemy[choice] -> SetDifficulty(atoi(al_get_config_value(iniFile, message, "difficulty")));
            enemy[choice] -> SetTempDestinationY(0);
            enemy[choice] -> SetTempDestinationX(0);
            enemy[choice] -> SetWallAtPath(false);
            enemy[choice] -> SetFirstmovement(false);
            enemy[choice] -> SetAmmoTimer(0);
            enemy[choice] -> SetTempDirection(0);
            enemy[choice] -> SetDirectionCounter(0);
            enemy[choice] -> SetCanShoot(true);
            enemy[choice] -> SetTarGetAhead(false);
            enemy[choice] -> SetAttack(false);
            enemy[choice] -> SetDestinationX(0);
            enemy[choice] -> SetDestinationY(0);
            enemy[choice] -> SetWallID(0);
            enemy[choice] -> SetRespawnDelayTimer(0);

            while(enemy[choice] -> GetColision())
            {
                enemy[choice] -> CheckPlace(wall, player, enemy);

                if(!enemy[choice] -> GetColision())
                    break;

                enemy[choice] -> SetX(rand()%(BATTLEFIELD_WIDTH)/TANK_SIZE * TANK_SIZE);
                enemy[choice] -> SetY(rand()%(BATTLEFIELD_HEIGHT)/TANK_SIZE * TANK_SIZE);
            }

            enemy[choice] -> SetTempX(enemy[choice] -> GetX());
            enemy[choice] -> SetTempY(enemy[choice] -> GetY());
            enemy[choice] -> SetDead(false);
        }
    }
    SetTarGet(enemy, player);

    al_destroy_config(iniFile);
}

void Enemy::Spawn(short _x, short _y, short _life, short _ammoSpeed, short _direction, short _ammoDelay, short _difficulty, Wall **wall, Player * player, Enemy **enemy)
{
    direction = _direction;
    life = _life;
    x = (_x/TANK_SIZE) *TANK_SIZE;
    y = (_y/TANK_SIZE) *TANK_SIZE;
    ammoSpeed = _ammoSpeed;
    colision = true;
    ammoDelay = _ammoDelay;
    difficulty = _difficulty;
    stop = false;
    canShoot = true;
    tempDirection = 0;
    directionCounter = 0;
    destinationX = 0;
    destinationY = 0;
    tarGetAhead = false;
    wallAtPath = false;
    firstmovement = false;
    ammoTimer = 0;
    tempDestinationX = 0;
    tempDestinationY = 0;
    respawnDelayTimer = 0;
    attack = false;
    wallID = 0;

    while(colision == true)
    {
        this -> CheckPlace(wall, player, enemy);

        if(!colision)
            break;

        x = ((rand()%(BATTLEFIELD_WIDTH))/TANK_SIZE) *TANK_SIZE;
        x = ((rand()%(BATTLEFIELD_HEIGHT))/TANK_SIZE) *TANK_SIZE;
    }

    tempX = x;
    tempY = y;
    dead = false;
    SetTarGet(enemy, player);
};

void Enemy::CheckPlace(Wall **wall, Player * player, Enemy **enemy)
{
    for (short i=0; i<OBSTACLES ; i++)
    {
        if(wall[i] -> GetVisible())
        {
            if(wall[i] -> GetBase())//more space when it is base
            {
                if(x > wall[i] -> GetX() - (3*FREE_SPACE) && x < wall[i] -> GetX() + OBSTACLE_SIZE + (3*FREE_SPACE))
                    if(y + OBSTACLE_SIZE > wall[i] -> GetY() - (3*FREE_SPACE) && y < wall[i] -> GetY() + OBSTACLE_SIZE + (3*FREE_SPACE))
                    {
                        colision = true;
                        return;
                    }
            }
            else
            {
                if(x > wall[i] -> GetX() - OBSTACLE_SIZE && x < wall[i] -> GetX() + OBSTACLE_SIZE )
                    if(y + OBSTACLE_SIZE > wall[i] -> GetY() && y < wall[i] -> GetY() + OBSTACLE_SIZE )
                    {
                        colision = true;
                        return;
                    }
            }
        }
    }

    if(player->GetActive())
    {
        if(x > player -> GetX() - FREE_SPACE && x < player -> GetX() + TANK_SIZE + FREE_SPACE)
            if(y + TANK_SIZE > player -> GetY() - FREE_SPACE && y < player -> GetY() + TANK_SIZE + FREE_SPACE)
            {
                colision = true;
                return;
            }
    }

    for(short j=0; j < ENEMIES; j++)
    {
        if(!enemy[j] -> GetDead() && this != enemy[j])
        {
            if(x > enemy[j] -> GetX() - FREE_SPACE && x < enemy[j] -> GetX() + TANK_SIZE + FREE_SPACE)
                if(y + TANK_SIZE > enemy[j] -> GetY() - FREE_SPACE && y < enemy[j] -> GetY() + TANK_SIZE + FREE_SPACE)
                {
                    colision = true;
                    return;
                }
        }
    }

    colision = false;
};

short Enemy::CheckCollision(Wall **wall, Player * player, Enemy **enemy, Bonus **bonus)
{
    if(!dead)
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->GetVisible())
            {
                if(x >= wall[i]->GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=wall[i]->GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= wall[i]->GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= wall[i]->GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    x = tempX;
                    y = tempY;

                    if(wall[i]->GetDestroyable())
                    {
                        if(wall[i]->GetBase())
                        {
                            stop = true;
                            return 5; //base
                        }
                        else
                            return 3; //destroyable
                    }
                    else
                        return 1;  //immortal wall
                }
            }
        }

        if(player->GetActive())
        {
            if(x >= player -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=player -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                x = tempX;
                y = tempY;
                stop = true;
                return 4;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> GetDead() && this!=enemy[j])
            {
                if(x >= enemy[j] -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=enemy[j] -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= enemy[j] -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= enemy[j] -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    x = tempX;
                    y = tempY;
                    return 2;
                }
            }
        }

        for (short i=0; i<BONUSES ; i++)
        {
            if(bonus[i]->GetVisible())
            {
                if(x >= bonus[i]->GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=bonus[i]->GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= bonus[i]->GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= bonus[i]->GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                    bonus[i]->SetVisible(false);
            }
        }
    }

    return 0;
};

short CheckEnemyAlive(Enemy **enemy)
{
    short temp=0;
    for(short i=0; i<ENEMIES; i++)
    {
        if(!enemy[i]->GetDead())
            temp++;
    }

    return temp;
}

bool Enemy::CheckAimWall(Wall **wall, Enemy ** enemy)
{
    if(!dead)
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->GetVisible() && wall[i] -> GetDestroyable() && !wall[i] -> GetBase())
            {
                switch(direction)
                {
                case 0:
                {
                    if(x <= wall[i] -> GetX() && y + 21 >= wall[i] -> GetY() - ROCKET_Y  && y + 21 <= wall[i] -> GetY() + OBSTACLE_SIZE)
                    {
                        bool value = this -> CheckAimImmortallWall(wall, wall[i] -> GetX(), wall[i] -> GetY());
                        bool valueF = this -> CheckAimEnemy(enemy, wall[i] -> GetX(), wall[i] -> GetY());

                        if(value == true && valueF == true)
                        {
                            wallID = i;
                            return true;
                        }
                    }
                    break;
                }
                case 1:
                {
                    if(x >= wall[i] -> GetX() && y + 21 >= wall[i] -> GetY() - ROCKET_Y  && y + 21 <= wall[i] -> GetY() + OBSTACLE_SIZE)
                    {
                        bool value = this -> CheckAimImmortallWall(wall, wall[i] -> GetX(), wall[i] -> GetY());
                        bool valueF = this -> CheckAimEnemy(enemy, wall[i] -> GetX(), wall[i] -> GetY());

                        if(value == true && valueF == true)
                        {
                            wallID = i;
                            return true;
                        }
                    }
                    break;
                }
                case 2://dol
                {
                    if(x + 21 >= wall[i] -> GetX() - ROCKET_Y && x + 21 <= wall[i] -> GetX() + OBSTACLE_SIZE && y <= wall[i] -> GetY())
                    {
                        bool value = this -> CheckAimImmortallWall(wall, wall[i] -> GetX(), wall[i] -> GetY());
                        bool valueF = this -> CheckAimEnemy(enemy, wall[i] -> GetX(), wall[i] -> GetY());

                        if(value == true && valueF == true)
                        {
                            wallID = i;
                            return true;
                        }
                    }
                    break;
                }
                case 3:
                {
                    if(x + 29 >= wall[i] -> GetX() - ROCKET_Y && x + 29 <= wall[i] -> GetX() + OBSTACLE_SIZE && y >= wall[i] -> GetY())
                    {
                        bool value = this -> CheckAimImmortallWall(wall, wall[i] -> GetX(), wall[i] -> GetY());
                        bool valueF = this -> CheckAimEnemy(enemy, wall[i] -> GetX(), wall[i] -> GetY());

                        if(value == true && valueF == true)
                        {
                            wallID = i;
                            return true;
                        }
                    }
                    break;
                }
                }
            }
        }
    }
    return false;
}

bool Enemy::CheckAimImmortallWall(Wall **wall, short _x, short _y)
{
//can shoot?
    if(!dead)
    {
        for (short i=0; i<OBSTACLES; i++)
        {
            if(wall[i]->GetVisible() && !wall[i] -> GetDestroyable() && !wall[i] -> GetBase())
            {
                switch(direction)
                {
                case 0:
                {
                    if(x <= wall[i] -> GetX() && y + 21 >= wall[i] -> GetY() - ROCKET_Y  && y + 21 <= wall[i] -> GetY() + OBSTACLE_SIZE)
                    {
                        if(wall[i] -> GetX() < _x)
                            return false;
                    }

                    break;
                }
                case 1:
                {
                    if(x >= wall[i] -> GetX() && y + 21 >= wall[i] -> GetY() - ROCKET_Y  && y + 21 <= wall[i] -> GetY() + OBSTACLE_SIZE)
                    {
                        if(wall[i] -> GetX() > _x)
                            return false;
                    }

                    break;
                }
                case 2://down
                {
                    if(x + 21 >= wall[i] -> GetX() - ROCKET_Y && x + 21 <= wall[i] -> GetX() + OBSTACLE_SIZE && y <= wall[i] -> GetY())
                    {
                        if(wall[i] -> GetY() < _y)
                            return false;
                    }

                    break;
                }
                case 3:
                {
                    if(x + 29 >= wall[i] -> GetX() - ROCKET_Y && x + 29 <= wall[i] -> GetX() + OBSTACLE_SIZE && y >= wall[i] -> GetY())
                    {
                        if(wall[i] -> GetY() > _y)
                            return false;
                    }

                    break;
                }
                }
            }
        }
    }

    return true;
}

bool Enemy::CheckAimPlayer(Player *player, Enemy ** enemy, Wall ** wall)
{
    if(!dead)
    {
        if(player -> GetActive())
        {
            switch(direction)
            {
            case 0:
            {
                if(x <= player -> GetX() && y + 21 >= player -> GetY() - ROCKET_Y  && y + 21 <= player -> GetY() + TANK_SIZE)
                {
                    bool value = this -> CheckAimImmortallWall(wall, player -> GetX(), player -> GetY());
                    bool valueF = this -> CheckAimEnemy(enemy, player -> GetX(), player -> GetY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 1:
            {
                if(x >= player -> GetX() && y + 21 >= player -> GetY() - ROCKET_Y  && y + 21 <= player -> GetY() + TANK_SIZE)
                {
                    bool value = this -> CheckAimImmortallWall(wall, player -> GetX(), player -> GetY());
                    bool valueF = this -> CheckAimEnemy(enemy, player -> GetX(), player -> GetY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 2://dol
            {
                if(x + 21 >= player -> GetX() - ROCKET_Y && x + 21 <= player -> GetX() + TANK_SIZE && y <= player -> GetY())
                {
                    bool value = this -> CheckAimImmortallWall(wall, player -> GetX(), player -> GetY());
                    bool valueF = this -> CheckAimEnemy(enemy, player -> GetX(), player -> GetY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 3:
            {
                if(x + 29 >= player -> GetX() - ROCKET_Y && x + 29 <= player -> GetX() + TANK_SIZE && y >= player -> GetY())
                {
                    bool value = this -> CheckAimImmortallWall(wall, player -> GetX(), player -> GetY());
                    bool valueF = this -> CheckAimEnemy(enemy, player -> GetX(), player -> GetY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            }
        }
    }
    return false;
}

bool Enemy::CheckAimBase(Wall **wall, short id, Enemy ** enemy)
{
    if(!dead)
    {
        if(wall[id] -> GetBase() && wall[id] -> GetVisible())
        {
            switch(direction)
            {
            case 0:
            {
                if(x <= wall[id] -> GetX() && y + 21 >= wall[id] -> GetY() - ROCKET_Y  && y + 21 <= wall[id] -> GetY() + OBSTACLE_SIZE)
                {
                    bool value = this -> CheckAimImmortallWall(wall, wall[id] -> GetX(), wall[id] -> GetY());
                    bool valueF = this -> CheckAimEnemy(enemy, wall[id] -> GetX(), wall[id] -> GetY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 1:
            {
                if(x >= wall[id] -> GetX() && y + 21 >= wall[id] -> GetY() - ROCKET_Y  && y + 21 <= wall[id] -> GetY() + OBSTACLE_SIZE)
                {
                    bool value = this -> CheckAimImmortallWall(wall, wall[id] -> GetX(), wall[id] -> GetY());
                    bool valueF = this -> CheckAimEnemy(enemy, wall[id] -> GetX(), wall[id] -> GetY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 2://dol
            {
                if(x + 21 >= wall[id] -> GetX() - ROCKET_Y && x + 21 <= wall[id] -> GetX() + OBSTACLE_SIZE && y <= wall[id] -> GetY())
                {
                    bool value = this -> CheckAimImmortallWall(wall, wall[id] -> GetX(), wall[id] -> GetY());
                    bool valueF = this -> CheckAimEnemy(enemy, wall[id] -> GetX(), wall[id] -> GetY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 3:
            {
                if(x + 29 >= wall[id] -> GetX() - ROCKET_Y && x + 29 <= wall[id] -> GetX() + OBSTACLE_SIZE && y >= wall[id] -> GetY())
                {
                    bool value = this -> CheckAimImmortallWall(wall, wall[id] -> GetX(), wall[id] -> GetY());
                    bool valueF = this -> CheckAimEnemy(enemy, wall[id] -> GetX(), wall[id] -> GetY());

                    if(value == true && valueF == true)
                        return true;
                }
                break;
            }
            }
        }
    }
    return false;
}

bool Enemy::CheckAimEnemy(Enemy **enemy, short _x, short _y)
{
//czy mozna strzelac czy nie
    if(!dead)
    {
        for (short i=0; i<ENEMIES ; i++)
        {
            if(!enemy[i]->GetDead() && enemy[i] != this)
            {
                switch(direction)
                {
                case 0:
                {
                    if(x <= enemy[i] -> GetX() && y + 21 >= enemy[i] -> GetY() - ROCKET_Y  && y + 21 <= enemy[i] -> GetY() + TANK_SIZE)
                    {
                        if(enemy[i] -> GetX() < _x)
                            return false;
                    }

                    break;
                }
                case 1:
                {
                    if(x >= enemy[i] -> GetX() && y + 21 >= enemy[i] -> GetY() - ROCKET_Y  && y + 21 <= enemy[i] -> GetY() + TANK_SIZE)
                    {
                        if(enemy[i] -> GetX() > _x)
                            return false;
                    }

                    break;
                }
                case 2://dol
                {
                    if(x + 21 >= enemy[i] -> GetX() - ROCKET_Y && x + 21 <= enemy[i] -> GetX() + TANK_SIZE && y <= enemy[i] -> GetY())
                    {
                        if(enemy[i] -> GetY() < _y)
                            return false;
                    }
                    break;
                }
                case 3:
                {
                    if(x + 29 >= enemy[i] -> GetX() - ROCKET_Y && x + 29 <= enemy[i] -> GetX() + TANK_SIZE && y >= enemy[i] -> GetY())
                    {
                        if(enemy[i] -> GetY() > _y)
                            return false;
                    }

                    break;
                }
                }
            }
        }
    }
    return true;
}

bool Enemy::SearchForDirection()
{
    switch(id % 4)
    {
    case 0:
    {
        for(short i=0; i< BATTLEFIELD_WIDTH; i++) //x
            for(short j=0; j< BATTLEFIELD_HEIGHT; j++)
            {
                if(Enemy::isPlayer[i][j] < 2)
                {
                    destinationX = i;
                    destinationY = j;
                    return true;
                }
            }
        break;
    }
    case 1:
    {
        for(short i=BATTLEFIELD_WIDTH-1; i >= 0; i--)
            for(short j=BATTLEFIELD_HEIGHT-1; j >= 0; j--)
            {
                if(Enemy::isPlayer[i][j] < 2)
                {
                    destinationX = i;
                    destinationY = j;
                    return true;
                }
            }
        break;
    }

    case 2:
    {
        for(short i=BATTLEFIELD_WIDTH-1; i >= 0; i--)
            for(short j=1; j< BATTLEFIELD_HEIGHT; j++)
            {
                if(Enemy::isPlayer[i][j] < 2)
                {
                    destinationX = i;
                    destinationY = j;
                    return true;
                }
            }
        break;
    }

    case 3:
    {
        for(short i=0; i< BATTLEFIELD_WIDTH; i++)
            for(short j=BATTLEFIELD_HEIGHT-1; j>= 0; j--)
            {
                if(Enemy::isPlayer[i][j] < 2)
                {
                    destinationX = i;
                    destinationY = j;
                    return true;
                }
            }
        break;
    }

    }

    return false;
}

void Enemy::CheckForBase(Wall ** wall, Enemy ** enemy)
{
    if(Enemy::hasBase == false)
    {
        for(short i=0; i < OBSTACLES && Enemy::hasBase == false; i++)
        {
            if(wall[i] -> GetBase() && wall[i] -> GetVisible())
            {
                for (short k = 0 ; k < 4 && Enemy::hasBase == false; k++)
                {
                    if(k == 0)
                    {
                        short j= wall[i] -> GetY();
                        for (short k = wall[i] -> GetX() ; k <= wall[i] -> GetX() + OBSTACLE_SIZE && Enemy::hasBase == false; k++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if( Enemy::isPlayer[k][j] == 4)
                            {
                                Enemy::hasBase = true;
                                Wall::baseID = i;
                                SetBaseCoord(enemy, wall, 0);
                            }
                        }
                    }
                    else if(k == 1)
                    {
                        short j= wall[i] -> GetY() + OBSTACLE_SIZE;
                        for (short k = wall[i] -> GetX() ; k <= wall[i] -> GetX() + OBSTACLE_SIZE && Enemy::hasBase == false; k++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if( Enemy::isPlayer[k][j] == 4)
                            {
                                Enemy::hasBase = true;
                                Wall::baseID = i;
                                SetBaseCoord(enemy, wall,0);
                            }
                        }
                    }
                    else if(k == 2)
                    {
                        short k= wall[i] -> GetX();
                        for (short j = wall[i] -> GetY(); j <= wall[i] -> GetY() + OBSTACLE_SIZE && Enemy::hasBase == false ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if( Enemy::isPlayer[k][j] == 4)
                            {
                                Enemy::hasBase = true;
                                Wall::baseID = i;
                                SetBaseCoord(enemy, wall,0);
                            }
                        }
                    }
                    else if(k == 3)
                    {
                        short k= wall[i] -> GetX() + OBSTACLE_SIZE;
                        for (short j = wall[i] -> GetY(); j <= wall[i] -> GetY() + OBSTACLE_SIZE && Enemy::hasBase == false ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if( Enemy::isPlayer[k][j] == 4)
                            {
                                Enemy::hasBase = true;
                                Wall::baseID = i;
                                SetBaseCoord(enemy, wall,0);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Enemy::CheckForPlayer(Player *player, Enemy **enemy)
{
    for (short k = 0 ; k < 4 && player -> GetActive(); k++)
    {
        if(k == 0)
        {
            short j = player -> GetY();
            for(short i = player -> GetX() ; i <= player -> GetX() + TANK_SIZE; i++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[i][j] == 3)
                {
                    Enemy::hasPlayer = true;
                    Enemy::playerTimer = 0;
                    this -> SetPlayerCoord(enemy, player);
                    return;
                }
            }
        }
        else if(k == 1)
        {
            short j= player -> GetY() + TANK_SIZE;
            for(short i = player -> GetX() ; i <= player -> GetX() + TANK_SIZE; i++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[i][j] == 3)
                {
                    Enemy::hasPlayer = true;
                    Enemy::playerTimer = 0;
                    this -> SetPlayerCoord(enemy, player);
                    return;
                }
            }
        }
        else if(k == 2)
        {
            short i= player -> GetX();
            for(short j = player -> GetY() ; j <= player -> GetY() + TANK_SIZE; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[i][j] == 3)
                {
                    Enemy::hasPlayer = true;
                    Enemy::playerTimer = 0;
                    this -> SetPlayerCoord(enemy, player);
                    return;
                }
            }
        }
        else if(k == 3)
        {
            short i= player -> GetX() + TANK_SIZE;
            for(short j = player -> GetY() ; j <= player -> GetY() + TANK_SIZE; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[i][j] == 3)
                {
                    Enemy::hasPlayer = true;
                    Enemy::playerTimer = 0;
                    this -> SetPlayerCoord(enemy, player);
                    return;
                }
            }
        }
    }
}

bool Enemy::CheckDirection(short direction, Wall ** wall, Enemy ** enemy, Player *player, short moves)
{
    switch(direction)
    {
    case 0:
    {
        if(x + TANK_SPEED > BATTLEFIELD_WIDTH)
            return false;

        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->GetVisible())
            {
                if(x + (moves*TANK_SPEED) >= wall[i]->GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x + (moves*TANK_SPEED) <=wall[i]->GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= wall[i]->GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y <= wall[i]->GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    if(wall[i]->GetDestroyable())
                    {
                        if(wall[i]->GetBase())
                        {
                            tarGetAhead = true;
                            stop = true;
                            return true; //baza
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
        }

        if(player->GetActive())
        {
            if(x + (moves*TANK_SPEED) >= player -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x + (moves*TANK_SPEED) <=player -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                tarGetAhead = true;
                stop = true;
                return true;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> GetDead() && this!=enemy[j])
            {
                if(x + (moves*TANK_SPEED) >= enemy[j] -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x + (moves*TANK_SPEED) <=enemy[j] -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= enemy[j] -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= enemy[j] -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    return false;
                }
            }
        }

        break;
    }
    case 1:
    {
        if(x - TANK_SPEED < 0)
            return false;

        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->GetVisible())
            {
                if(x - (moves*TANK_SPEED) >= wall[i]->GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x - (moves*TANK_SPEED) <=wall[i]->GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= wall[i]->GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y <= wall[i]->GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    if(wall[i]->GetDestroyable())
                    {
                        if(wall[i]->GetBase())
                        {
                            tarGetAhead = true;
                            stop = true;
                            return true; //baza
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
        }

        if(player->GetActive())
        {
            if(x - (moves*TANK_SPEED) >= player -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x - (moves*TANK_SPEED)<=player -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                tarGetAhead = true;
                stop = true;
                return true;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> GetDead() && this!=enemy[j])
            {
                if(x - (moves*TANK_SPEED) >= enemy[j] -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x - (moves*TANK_SPEED)<=enemy[j] -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= enemy[j] -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= enemy[j] -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    return false;
                }
            }
        }

        break;
    }
    case 2:
    {
        if(y + (moves*TANK_SPEED) > BATTLEFIELD_HEIGHT)
            return false;

        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->GetVisible())
            {
                if(x >= wall[i]->GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=wall[i]->GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y + (moves*TANK_SPEED) >= wall[i]->GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y + (moves*TANK_SPEED) <= wall[i]->GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    if(wall[i]->GetDestroyable())
                    {
                        if(wall[i]->GetBase())
                        {
                            tarGetAhead = true;
                            stop = true;
                            return true; //baza
                        }
                        else
                            return false; //destroyable
                    }
                    else
                        return false;  //immortal
                }
            }
        }

        if(player->GetActive())
        {
            if(x >= player -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=player -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y + (moves*TANK_SPEED) >= player -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y + (moves*TANK_SPEED)<= player -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                tarGetAhead = true;
                stop = true;
                return true;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> GetDead() && this!=enemy[j])
            {
                if(x >= enemy[j] -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=enemy[j] -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y + (moves*TANK_SPEED) >= enemy[j] -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y + (moves*TANK_SPEED)<= enemy[j] -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    return false;
                }
            }
        }

        break;
    }
    case 3:
    {
        if(y - (moves*TANK_SPEED) < 0)
            return false;

        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->GetVisible())
            {
                if(x >= wall[i]->GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=wall[i]->GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y - (moves*TANK_SPEED) >= wall[i]->GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y - (moves*TANK_SPEED) <= wall[i]->GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    if(wall[i]->GetDestroyable())
                    {
                        if(wall[i]->GetBase())
                        {
                            tarGetAhead = true;
                            stop = true;
                            return true; //baza
                        }
                        else
                            return false; //zniszczalna
                    }
                    else
                        return false;  //niezniszczalna
                }
            }
        }

        if(player->GetActive())
        {
            if(x >= player -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=player -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y - (moves*TANK_SPEED) >= player -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y - (moves*TANK_SPEED)<= player -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                tarGetAhead = true;
                stop = true;
                return true;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> GetDead() && this!=enemy[j])
            {
                if(x >= enemy[j] -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=enemy[j] -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y - (moves*TANK_SPEED) >= enemy[j] -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y - (moves*TANK_SPEED)<= enemy[j] -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    return false;
                }
            }
        }

        break;
    }
    }

    return true;
}

void Enemy::Shoot(Rocket ** rocket)
{
    canShoot = false;
    ammoTimer = 1;

    if(Rocket::rocketsCounter[1] < ENEMY_MAX_SHOOTS)
    {
        short choice=GiveRocketID(rocket);

        switch(direction)
        {
        case 0:
        {
            rocket[choice] -> SetDirection(0);
            rocket[choice] -> SetX(x + 51);
            rocket[choice] -> SetY(y + 21);

            break; //right
        }
        case 1:
        {
            rocket[choice] -> SetDirection(1);
            rocket[choice] -> SetX(x - 16);
            rocket[choice] -> SetY(y + 21);

            break; //left
        }
        case 2:
        {
            rocket[choice] -> SetDirection(2);
            rocket[choice] -> SetX(x + 21);
            rocket[choice] -> SetY(y + 60);

            break; //down
        }
        case 3:
        {
            rocket[choice] -> SetDirection(3);
            rocket[choice] -> SetX(x + 29);
            rocket[choice] -> SetY(y - 14);

            break; //up
        }
        }
        Rocket::rocketsCounter[1]++;
        rocket[choice] -> SetSpeed(ammoSpeed);
        rocket[choice] -> SetVisible(true);
        rocket[choice] -> SetTeam(false);

        al_play_sample(sound[0], 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }
}

void Enemy::CheckNearbyArea(Wall ** wall, Enemy ** enemy, Player * player)
{
    switch(direction)
    {
    case 0:
    {
        for (short i=0; i < OBSTACLES ; i++)
        {
            if(wall[i] -> GetVisible())
            {
                if( (wall[i] -> GetX() + OBSTACLE_SIZE) < x - VIEW_RANGE ) //1 wall is too far behind
                    continue;

                if(wall[i] -> GetY() + OBSTACLE_SIZE <  y - VIEW_RANGE) //2 enemy is under wall
                    continue;

                if(wall[i] -> GetY() >  y + VIEW_RANGE + TANK_SIZE)                 //3 enemy is up the wall
                    continue;

                //1 condition wall at left
                //2 condition complete wall in sight
                //3 wall at right

                if((wall[i] -> GetY() < y - VIEW_RANGE) && (wall[i] -> GetY() + OBSTACLE_SIZE > y - VIEW_RANGE) && (wall[i] -> GetX() + MARGIN_SIZE >= x + TANK_SIZE)) // 1. z gory wystaje ale widac przed czolgiem
                {
                    //behind wall we Set 1
                    for(int k = wall[i] -> GetX() + OBSTACLE_SIZE - MARGIN_SIZE ; k < REAL_BATTLEFIELD_WIDTH ; k++ )
                        for(int j = y - VIEW_RANGE ; j <= wall[i] -> GetY() + OBSTACLE_SIZE + MARGIN_SIZE ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }

                else if((wall[i] -> GetY() > y - VIEW_RANGE) && (wall[i] -> GetY() + OBSTACLE_SIZE < y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> GetX() + MARGIN_SIZE >= x + OBSTACLE_SIZE)) //2. cala widac
                {
                    if(wall[i] -> GetX() < x + TANK_SIZE + BLIND_RANGE)
                    {
                        for(int k = wall[i] -> GetX() + OBSTACLE_SIZE - MARGIN_SIZE ; k < REAL_BATTLEFIELD_WIDTH ; k++ )
                            for(int j = wall[i] -> GetY() - VIEW_RANGE ; j <= wall[i] -> GetY() + OBSTACLE_SIZE + VIEW_RANGE ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                    else
                    {
                        for(int k = wall[i] -> GetX() + OBSTACLE_SIZE - MARGIN_SIZE ; k < REAL_BATTLEFIELD_WIDTH ; k++ )
                            for(int j = wall[i] -> GetY() - MARGIN_SIZE ; j <= wall[i] -> GetY() + OBSTACLE_SIZE + MARGIN_SIZE ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                }
                else if((wall[i] -> GetY() < y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> GetY() + OBSTACLE_SIZE > y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> GetX() + MARGIN_SIZE >= x + OBSTACLE_SIZE))
                {
                    for(int k = wall[i] -> GetX() + OBSTACLE_SIZE - MARGIN_SIZE ; k < REAL_BATTLEFIELD_WIDTH ; k++ )
                        for(int j = wall[i] -> GetY() - MARGIN_SIZE ; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
            }
        }

        for (short k = x - VIEW_RANGE ; k < REAL_BATTLEFIELD_WIDTH ; k++)
        {
            for (short j = y - VIEW_RANGE; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || k < 0)
                    continue;

                if(Enemy::isPlayer[k][j] == 0 || Enemy::isPlayer[k][j] == 4)
                    Enemy::isPlayer[k][j] = 3;
            }
        }

        this -> CheckForPlayer(player, enemy);

        for (short i= x - VIEW_RANGE ; i < REAL_BATTLEFIELD_WIDTH ; i++)
            for (short j = y - VIEW_RANGE; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[j][i] == 2 || Enemy::isPlayer[j][i] == 3)
                    Enemy::isPlayer[j][i] = 4;
                else if(Enemy::isPlayer[j][i] == 1)
                    Enemy::isPlayer[j][i] = 0;
            }
        break;
    }
    case 1:
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i] -> GetVisible())
            {
                if( wall[i] -> GetX() > x + VIEW_RANGE + TANK_SIZE)
                    continue;

                if(wall[i] -> GetY() + OBSTACLE_SIZE <  y - VIEW_RANGE)
                    continue;

                if(wall[i] -> GetY() >  y + VIEW_RANGE + TANK_SIZE)
                    continue;

                if((wall[i] -> GetY() < y - VIEW_RANGE) && (wall[i] -> GetY() + OBSTACLE_SIZE > y - VIEW_RANGE) && (wall[i] -> GetX() + OBSTACLE_SIZE <= x + MARGIN_SIZE)) // 1. z gory ale widac przed czolgiem
                {
                    for(int k = wall[i] -> GetX() + MARGIN_SIZE ; k > 0 ; k-- )
                        for(int j = y - VIEW_RANGE ; j <= wall[i] -> GetY() + OBSTACLE_SIZE + MARGIN_SIZE ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }

                else if((wall[i] -> GetY() > y - VIEW_RANGE) && (wall[i] -> GetY() + OBSTACLE_SIZE < y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> GetX() + OBSTACLE_SIZE <= x + MARGIN_SIZE))
                {
                    if(wall[i] -> GetX() + OBSTACLE_SIZE > x - BLIND_RANGE)
                    {
                        for(int k = wall[i] -> GetX() + MARGIN_SIZE ; k > 0 ; k-- )
                            for(int j = wall[i] -> GetY() - VIEW_RANGE ; j <= wall[i] -> GetY() + OBSTACLE_SIZE + VIEW_RANGE ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                    else
                    {
                        for(int k = wall[i] -> GetX() + MARGIN_SIZE ; k > 0 ; k-- )
                            for(int j = wall[i] -> GetY() - MARGIN_SIZE ; j <= wall[i] -> GetY() + OBSTACLE_SIZE + MARGIN_SIZE ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                }
                else if((wall[i] -> GetY() < y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> GetY() + OBSTACLE_SIZE > y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> GetX() + OBSTACLE_SIZE <= x + MARGIN_SIZE))
                {
                    for(int k = wall[i] -> GetX() + MARGIN_SIZE ; k >= 0 ; k-- )
                        for(int j = wall[i] -> GetY() - MARGIN_SIZE ; j <= y + VIEW_RANGE + TANK_SIZE; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
            }
        }

        for (short k = x + TANK_SIZE + VIEW_RANGE ; k >= 0 ; k--)
        {
            for (short j = y - VIEW_RANGE; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || k < 0)
                    continue;

                if(Enemy::isPlayer[k][j] == 0 || Enemy::isPlayer[k][j] == 4)
                    Enemy::isPlayer[k][j] = 3;
            }
        }

        this -> CheckForPlayer(player, enemy);

        for (short i = x + TANK_SIZE +VIEW_RANGE ; i >= 0 ; i--)
            for (short j = y - VIEW_RANGE; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[j][i] == 2 || Enemy::isPlayer[j][i] == 3)
                    Enemy::isPlayer[j][i] = 4;
                else if(Enemy::isPlayer[j][i] == 1)
                    Enemy::isPlayer[j][i] = 0;
            }
        break;
    }
    case 2:
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i] -> GetVisible())
            {
                if( wall[i] -> GetY() + OBSTACLE_SIZE < y - VIEW_RANGE )
                    continue;

                if(wall[i] -> GetX() + OBSTACLE_SIZE <  x - VIEW_RANGE)
                    continue;

                if(wall[i] -> GetX() >  x + VIEW_RANGE + TANK_SIZE)
                    continue;

                if(wall[i] -> GetX() < x - VIEW_RANGE && wall[i] -> GetX() + OBSTACLE_SIZE > x - VIEW_RANGE && wall[i] -> GetY() + MARGIN_SIZE >= y + TANK_SIZE)
                {
                    for(int k = x - VIEW_RANGE ; k <= wall[i] -> GetX() + OBSTACLE_SIZE + MARGIN_SIZE ; k++ )
                        for(int j = wall[i] -> GetY() + OBSTACLE_SIZE - MARGIN_SIZE ; j < REAL_BATTLEFIELD_HEIGHT ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
                else if(wall[i] -> GetX() > x - VIEW_RANGE && wall[i] -> GetX() + OBSTACLE_SIZE < x + TANK_SIZE + VIEW_RANGE && wall[i] -> GetY() + MARGIN_SIZE >= y + TANK_SIZE)
                {
                    if(wall[i] -> GetY() < y + TANK_SIZE + BLIND_RANGE )
                    {
                        for(int k = wall[i] -> GetX() - VIEW_RANGE ; k <= wall[i] -> GetX() + OBSTACLE_SIZE + VIEW_RANGE; k++ )
                            for(int j = wall[i] -> GetY() + OBSTACLE_SIZE - MARGIN_SIZE ; j < REAL_BATTLEFIELD_HEIGHT ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                    else
                    {
                        for(int k = wall[i] -> GetX() - MARGIN_SIZE ; k <= wall[i] -> GetX() + OBSTACLE_SIZE + MARGIN_SIZE; k++ )
                            for(int j = wall[i] -> GetY() + OBSTACLE_SIZE - MARGIN_SIZE ; j < REAL_BATTLEFIELD_HEIGHT ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                }
                else if(wall[i] -> GetX() < x + TANK_SIZE + VIEW_RANGE && wall[i] -> GetX() + OBSTACLE_SIZE > x + TANK_SIZE + VIEW_RANGE && wall[i] -> GetY() + MARGIN_SIZE >= y + TANK_SIZE)
                {
                    for(int k = wall[i] -> GetX() - MARGIN_SIZE ; k <= x + TANK_SIZE + VIEW_RANGE; k++ )
                        for(int j = wall[i] -> GetY() + OBSTACLE_SIZE - MARGIN_SIZE ; j < REAL_BATTLEFIELD_HEIGHT ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
            }
        }

        for (short k = x - VIEW_RANGE ; k <= x + VIEW_RANGE + TANK_SIZE; k++)
        {
            for (short j = y - VIEW_RANGE; j < REAL_BATTLEFIELD_HEIGHT ; j++)
            {
                if(k < 0 || j < 0)
                    continue;

                if(Enemy::isPlayer[k][j] == 0 || Enemy::isPlayer[k][j] == 4)
                    Enemy::isPlayer[k][j] = 3;
            }
        }

        this -> CheckForPlayer(player, enemy);

        for (short i= y - VIEW_RANGE ; i < REAL_BATTLEFIELD_HEIGHT ; i++)
            for (short j = x - VIEW_RANGE; j <= x + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(i < 0 || j < 0)
                    continue;

                if(Enemy::isPlayer[j][i] == 2 || Enemy::isPlayer[j][i] == 3)
                    Enemy::isPlayer[j][i] = 4;
                else if(Enemy::isPlayer[j][i] == 1)
                    Enemy::isPlayer[j][i] = 0;
            }
        break;
    }
    case 3:
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i] -> GetVisible())
            {
                if( wall[i] -> GetY() > y + VIEW_RANGE + TANK_SIZE)
                    continue;

                if(wall[i] -> GetX() + OBSTACLE_SIZE <  x - VIEW_RANGE)
                    continue;

                if(wall[i] -> GetX() >  x + VIEW_RANGE + TANK_SIZE)
                    continue;

                if(wall[i] -> GetX() < x - VIEW_RANGE && wall[i] -> GetX() + OBSTACLE_SIZE > x - VIEW_RANGE && wall[i] -> GetY() + OBSTACLE_SIZE <= y + MARGIN_SIZE )
                {
                    for(int k = x - VIEW_RANGE ; k <= wall[i] -> GetX() + OBSTACLE_SIZE + MARGIN_SIZE ; k++ )
                        for(int j = wall[i] -> GetY() + MARGIN_SIZE ; j >= 0 ; j--)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
                else if(wall[i] -> GetX() > x - VIEW_RANGE && wall[i] -> GetX() + OBSTACLE_SIZE < x + TANK_SIZE + VIEW_RANGE && wall[i] -> GetY() + OBSTACLE_SIZE <= y + MARGIN_SIZE )
                {
                    if(wall[i] -> GetY() + OBSTACLE_SIZE > y - BLIND_RANGE )
                    {
                        for(int k = wall[i] -> GetX() - VIEW_RANGE ; k <= wall[i] -> GetX() + OBSTACLE_SIZE + VIEW_RANGE; k++ )
                            for(int j = wall[i] -> GetY() + MARGIN_SIZE ; j >= 0 ; j--)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                    else
                    {
                        for(int k = wall[i] -> GetX() - MARGIN_SIZE ; k <= wall[i] -> GetX() + OBSTACLE_SIZE + MARGIN_SIZE; k++ )
                            for(int j = wall[i] -> GetY() + MARGIN_SIZE ; j >= 0 ; j--)
                            {

                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                }
                else if(wall[i] -> GetX() < x + TANK_SIZE + VIEW_RANGE && wall[i] -> GetX() + OBSTACLE_SIZE > x + TANK_SIZE + VIEW_RANGE && wall[i] -> GetY() + OBSTACLE_SIZE <= y + MARGIN_SIZE )
                {
                    for(int k = wall[i] -> GetX() - MARGIN_SIZE ; k <= x + TANK_SIZE + VIEW_RANGE; k++ )
                        for(int j = wall[i] -> GetY() + MARGIN_SIZE ; j >= 0 ; j--)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
            }
        }

        for (short k = x - VIEW_RANGE ; k <= x + VIEW_RANGE + TANK_SIZE; k++)
        {
            for (short j = y + VIEW_RANGE; j >= 0 ; j--)
            {
                if(j < 0 || k < 0)
                    continue;

                if(Enemy::isPlayer[k][j] == 0 || Enemy::isPlayer[k][j] == 4)
                    Enemy::isPlayer[k][j] = 3;
            }
        }

        this -> CheckForPlayer(player, enemy);

        for (short i= y + VIEW_RANGE ; i >= 0 ; i--)
            for (short j = x - VIEW_RANGE; j <= x + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[j][i] == 2 || Enemy::isPlayer[j][i] == 3)
                    Enemy::isPlayer[j][i] = 4;
                else if(Enemy::isPlayer[j][i] == 1)
                    Enemy::isPlayer[j][i] = 0;
            }

        break;
    }
    }
    this -> CheckForBase(wall,enemy);
}

bool Enemy::CheckPlayerFuture(short direction, Player *player, short moves)
{
    switch(direction)
    {
    case 0:
    {
        if(x + 2 > BATTLEFIELD_WIDTH)
            return false;

        if(player -> GetActive())
        {
            if(x + (moves*2) >= player -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x + (moves*2) <=player -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                return true;
            else
                return false;
        }

        break;
    }
    case 1:
    {
        if(x - TANK_SPEED < 0)
            return false;

        if(player->GetActive())
        {
            if(x - (moves*2) >= player -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x - (moves*2)<=player -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                return true;
            else
                return false;
        }


        break;
    }
    case 2:
    {
        if(y + (moves*2) > BATTLEFIELD_HEIGHT)
            return false;

        if(player->GetActive())
        {
            if(x >= player -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=player -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y + (moves*2) >= player -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y + (moves*2)<= player -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                return true;
            else
                return false;
        }


        break;
    }
    case 3:
    {
        if(y - (moves*2) < 0)
            return false;

        if(player->GetActive())
        {
            if(x >= player -> GetX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=player -> GetX()+OBSTACLE_SIZE-MARGIN_SIZE && y - (moves*2) >= player -> GetY()-OBSTACLE_SIZE+MARGIN_SIZE && y - (moves*2)<= player -> GetY()+OBSTACLE_SIZE-MARGIN_SIZE)
                return true;
            else
                return false;
        }

        break;
    }
    }

    return true;
}

void Enemy::CheckDestination(Wall ** wall)
{
    if (Enemy::isPlayer[destinationX][destinationY] > 1)
    {
        if(!this -> SearchForDirection())
            ClearPlayerArray(wall);
    }
}

void Enemy::FightCoord(Player *player, Wall ** wall, Enemy **enemy)
{
    switch(direction)
    {
    case 0 ... 1:
    {
        if(player -> GetY() > y)
        {
            attack = true;
            bool mozna = true;
            std::string route;
            if(player -> GetY() + TANK_SIZE > BATTLEFIELD_HEIGHT)
                mozna = false;

            if(mozna)
            {
                destinationY = player -> GetY() + TANK_SIZE;
                destinationX = player -> GetX();
                route = FindPath(enemy, wall, player, id, false, true);
            }

            if(mozna == true && route.at(0) != '5')
            {
                directionCounter = 0;
                tempDirection = this-> EnemyPilot(enemy, wall, player, true);
            }
            else
            {
                mozna = true;
                if(player -> GetY() - TANK_SIZE < 0)
                    mozna = false;

                if(mozna)
                {
                    destinationX = player -> GetX();
                    destinationY = player -> GetY() - TANK_SIZE;
                    route = FindPath(enemy, wall, player, id, false, true);
                }
                if(mozna && route.at(0) != '5')
                {
                    directionCounter = 0;
                    tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                }
                else
                {
                    mozna = true;
                    if(player -> GetX() + TANK_SIZE > BATTLEFIELD_WIDTH)
                        mozna = false;

                    if(mozna)
                    {
                        destinationX = player -> GetX() + TANK_SIZE;
                        destinationY = player -> GetY();
                        route = FindPath(enemy, wall, player, id, false, true);
                    }
                    if(mozna && route.at(0) != '5')
                    {
                        directionCounter = 0;
                        tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                    }
                    else
                    {
                        mozna = true;
                        if(player -> GetX() - TANK_SIZE > 0)
                            mozna = false;

                        if(mozna)
                        {
                            destinationX = player -> GetX() - TANK_SIZE;
                            destinationY = player -> GetY();
                            route = FindPath(enemy, wall, player, id, false, true);
                        }
                        if(mozna && route.at(0) != '5')
                        {
                            directionCounter = 0;
                            tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                        }
                        else
                        {
                            enemy[id] -> SetStop(true);
                            tempDirection = 5;
                        }
                    }
                }
            }
        }
        else if (player -> GetY() < y)
        {
            attack = true;
            bool mozna = true;
            std::string route;
            if(player -> GetY() - TANK_SIZE < 0)
                mozna = false;

            if(mozna)
            {
                destinationY = player -> GetY() - TANK_SIZE;
                destinationX = player -> GetX();
                route = FindPath(enemy, wall, player, id, false, true);
            }
            if(mozna && route.at(0) != '5')
            {
                directionCounter = 0;
                tempDirection = this-> EnemyPilot(enemy, wall, player, true);
            }
            else
            {
                mozna = true;
                if(player -> GetY() + TANK_SIZE > BATTLEFIELD_HEIGHT)
                    mozna = false;

                if(mozna)
                {
                    destinationX = player -> GetX();
                    destinationY = player -> GetY() + TANK_SIZE;
                    route = FindPath(enemy, wall, player, id, false, true);
                }
                if(mozna && route.at(0) != '5')
                {
                    directionCounter = 0;
                    tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                }
                else
                {
                    mozna = true;
                    if(player -> GetX() + TANK_SIZE > BATTLEFIELD_WIDTH)
                        mozna = false;

                    if(mozna)
                    {
                        destinationX = player -> GetX() + TANK_SIZE;
                        destinationY = player -> GetY();
                        route = FindPath(enemy, wall, player, id, false, true);
                    }
                    if(mozna && route.at(0) != '5')
                    {
                        directionCounter = 0;
                        tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                    }
                    else
                    {
                        mozna = true;
                        if(player -> GetX() - TANK_SIZE < 0)
                            mozna = false;

                        if(mozna)
                        {
                            destinationX = player -> GetX() - TANK_SIZE;
                            destinationY = player -> GetY();
                            route = FindPath(enemy, wall, player, id, false, true);
                        }
                        if(mozna && route.at(0) != '5')
                        {
                            directionCounter = 0;
                            tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                        }
                        else
                        {
                            enemy[id] -> SetStop(true);
                            tempDirection = 5;
                        }
                    }
                }
            }
        }
        break;
    }
    case 2 ... 3:
    {
        if(player -> GetX() > x)
        {
            attack = true;
            bool mozna = true;
            std::string route;
            if(player -> GetX() + TANK_SIZE > BATTLEFIELD_WIDTH)
                mozna = false;

            if(mozna)
            {
                destinationX = player -> GetX() + TANK_SIZE;
                destinationY = player -> GetY();
                route = FindPath(enemy, wall, player, id, false, true);
            }

            if(mozna && route.at(0) != '5')
            {
                directionCounter = 0;
                tempDirection = this-> EnemyPilot(enemy, wall, player, true);
            }
            else
            {
                mozna = true;
                if(player -> GetX() - TANK_SIZE < 0)
                    mozna = false;

                if(mozna)
                {
                    destinationX = player -> GetX() - TANK_SIZE;
                    destinationY = player -> GetY();
                    route = FindPath(enemy, wall, player, id, false, true);
                }
                if(route.at(0) != '5' && mozna)
                {
                    directionCounter = 0;
                    tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                }
                else
                {
                    mozna = true;
                    if(player -> GetY() + TANK_SIZE > BATTLEFIELD_HEIGHT)
                        mozna = false;

                    if(mozna)
                    {
                        destinationX = player -> GetX();
                        destinationY = player -> GetY() + TANK_SIZE;
                        route = FindPath(enemy, wall, player, id, false, true);
                    }
                    if(mozna && route.at(0) != '5')
                    {
                        directionCounter = 0;
                        tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                    }
                    else
                    {
                        mozna = true;
                        if(player -> GetY() - TANK_SIZE < 0)
                            mozna = false;

                        if(mozna)
                        {
                            destinationX = player -> GetX();
                            destinationY = player -> GetY() - TANK_SIZE;
                            route = FindPath(enemy, wall, player, id, false, true);
                        }
                        if(mozna && route.at(0) != '5')
                        {
                            directionCounter = 0;
                            tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                        }
                        else
                        {
                            enemy[id] -> SetStop(true);
                            tempDirection = 5;
                        }
                    }
                }
            }
        }
        else if (player -> GetX() < x)
        {

            attack = true;
            bool mozna = true;
            std::string route;
            if(player -> GetX() - TANK_SIZE < 0)
                mozna = false;

            if(mozna)
            {
                destinationX = player -> GetX() - TANK_SIZE;
                destinationY = player -> GetY();
                route = FindPath(enemy, wall, player, id, false, true);
            }
            if(mozna && route.at(0) != '5')
            {
                directionCounter = 0;
                tempDirection = this-> EnemyPilot(enemy, wall, player, true);
            }
            else
            {
                mozna = true;
                if(player -> GetX() + TANK_SIZE > BATTLEFIELD_WIDTH)
                    mozna = false;

                if(mozna)
                {
                    destinationX = player -> GetX() + TANK_SIZE;
                    destinationY = player -> GetY();
                    route = FindPath(enemy, wall, player, id, false, true);
                }
                if(mozna && route.at(0) != '5')
                {
                    directionCounter = 0;
                    tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                }
                else
                {
                    mozna = true;
                    if(player -> GetY() + TANK_SIZE > BATTLEFIELD_HEIGHT)
                        mozna = false;

                    if(mozna)
                    {
                        destinationX = player -> GetX();
                        destinationY = player -> GetY() + TANK_SIZE;
                        route = FindPath(enemy, wall, player, id, false, true);
                    }
                    if(mozna && route.at(0) != '5')
                    {
                        directionCounter = 0;
                        tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                    }
                    else
                    {
                        mozna = true;
                        if(player -> GetY() - TANK_SIZE < 0)
                            mozna = false;

                        if(mozna)
                        {
                            destinationX = player -> GetX();
                            destinationY = player -> GetY() - TANK_SIZE;
                            route = FindPath(enemy, wall, player, id, false, true);
                        }
                        if(mozna && route.at(0) != '5')
                        {
                            directionCounter = 0;
                            tempDirection = this-> EnemyPilot(enemy, wall, player, true);
                        }
                        else
                        {
                            enemy[id] -> SetStop(true);
                            tempDirection = 5;
                        }
                    }
                }
            }
        }
        break;
    }
    }
}

void SetTarGet(Enemy **enemy, Player *player)
{
    short enemyAlive = CheckEnemyAlive(enemy);

    if(Wall::baseExist)
    {
        if(Enemy::hasPlayer == false && Enemy::hasBase == false)
        {
            Enemy::attackBase[0] = true;
            Enemy::attackBase[1] = false;
            Enemy::attackBase[2] = false;
        }
        else
        {
            switch(enemyAlive)
            {
            case 1:
            {
                if(Enemy::hasPlayer == true && (Enemy::hasBase == false && Wall::baseExist == true))
                {
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> GetDead())
                        {
                            Enemy::attackBase[j] = false;
                            break;
                        }
                    }
                }
                else if(Enemy::hasPlayer == false && Enemy::hasBase == true)
                {
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> GetDead())
                        {
                            Enemy::attackBase[j] = true;
                            break;
                        }
                    }
                }
                else if(Enemy::hasPlayer == true && Enemy::hasBase == true)
                {
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> GetDead() && !enemy[j] -> GetAttack())
                        {
                            if(player -> GetLife() < 2)
                                Enemy::attackBase[j] = false;
                            else
                                Enemy::attackBase[j] = true;

                            break;
                        }
                    }
                }
                break;
            }
            case 2 ... 3:
            {
                if(Enemy::hasPlayer == true && (Enemy::hasBase == false && Wall::baseExist == true))
                {
                    bool tempSet = false;
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> GetDead())
                        {
                            if(!tempSet)
                            {
                                Enemy::attackBase[j] = true;
                                tempSet = true;
                            }
                            else
                                Enemy::attackBase[j] = false;
                        }
                    }
                }
                else if(Enemy::hasPlayer == false && Enemy::hasBase == true)
                {
                    bool tempSet = false;
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> GetDead())
                        {
                            if(!tempSet)
                            {
                                Enemy::attackBase[j] = true;
                                tempSet = true;
                            }
                            else
                                Enemy::attackBase[j] = false;

                        }
                    }
                }
                else if(Enemy::hasPlayer == true && Enemy::hasBase == true)
                {
                    bool tempSet = false;
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> GetDead())
                        {
                            if(!tempSet)
                            {
                                Enemy::attackBase[j] = true;
                                tempSet = true;
                            }
                            else
                                Enemy::attackBase[j] = false;
                        }
                    }
                }
                break;
            }
            }

        }
    }
}

short Enemy::EnemyPilot(Enemy **enemy, Wall **wall, Player *player, bool fight)
{
    std::string route;
    if(!fight)
        route = FindPath(enemy, wall, player, id, false, false);
    else
        route = FindPath(enemy, wall, player, id, false, true);

    wallAtPath = false;
    if(route.at(0) == '0')
    {
        tempDestinationY = (enemy[id] -> GetY()/TANK_SIZE) * TANK_SIZE;
        tempDestinationX = (enemy[id] -> GetX()/TANK_SIZE + 1) * TANK_SIZE;
        return 0;
    }
    else if(route.at(0) == '1')
    {
        tempDestinationY = (enemy[id] -> GetY()/TANK_SIZE + 1) * TANK_SIZE;
        tempDestinationX = (enemy[id] -> GetX()/TANK_SIZE) * TANK_SIZE;
        return 2;
    }
    else if(route.at(0) == '2')
    {
        tempDestinationY = (enemy[id] -> GetY()/TANK_SIZE) * TANK_SIZE;
        tempDestinationX = (enemy[id] -> GetX()/TANK_SIZE - 1)*TANK_SIZE;
        return 1;
    }
    else if(route.at(0) == '3')
    {
        tempDestinationY = (enemy[id] -> GetY()/TANK_SIZE - 1)*TANK_SIZE;
        tempDestinationX = (enemy[id] -> GetX() /TANK_SIZE) * TANK_SIZE;
        return 3;
    }
    else
    {
        std::string route;
        if(!fight)
            route = FindPath(enemy, wall, player, id, true, false);
        else
            route = FindPath(enemy, wall, player, id, true, true);

        wallAtPath = true;
        if(route.at(0) == '0')
        {
            tempDestinationY = (enemy[id] -> GetY()/TANK_SIZE) * TANK_SIZE;
            tempDestinationX = (enemy[id] -> GetX()/TANK_SIZE + 1) * TANK_SIZE;
            return 0;
        }

        else if(route.at(0) == '1')
        {
            tempDestinationY = (enemy[id] -> GetY()/TANK_SIZE + 1) * TANK_SIZE;
            tempDestinationX = (enemy[id] -> GetX()/TANK_SIZE) * TANK_SIZE;
            return 2;
        }
        else if(route.at(0) == '2')
        {
            tempDestinationY = (enemy[id] -> GetY()/TANK_SIZE) * TANK_SIZE;
            tempDestinationX = (enemy[id] -> GetX()/TANK_SIZE - 1)*TANK_SIZE;
            return 1;
        }
        else if(route.at(0) == '3')
        {
            tempDestinationY = (enemy[id] -> GetY()/TANK_SIZE - 1)*TANK_SIZE;
            tempDestinationX = (enemy[id] -> GetX() /TANK_SIZE) * TANK_SIZE;
            return 3;
        }
    }

    return 5;
};
/*
0 - right
1 - down
2 - left
3 - up
*/

void  Enemy::MoveCorrection(Wall **wall, Player *player, Enemy **enemy, Bonus **bonus)
{
    short howMuch=0;
    if(x % TANK_SIZE != 0 && tempDirection > 1)
    {
        howMuch = x % TANK_SIZE ;
        if(howMuch <= 25 && this -> CheckDirection(1, wall, enemy, player, 1))
        {
            x -= 1;
        }
        else if (howMuch > 25 && this -> CheckDirection(0, wall, enemy, player, 1))
        {
            x += 1;
        }
        this -> CheckCollision(wall, player, enemy, bonus);
    }
    else if(y % TANK_SIZE != 0 && tempDirection < 2)
    {
        howMuch = y % TANK_SIZE ;
        if(howMuch <= 25 && this -> CheckDirection(3, wall, enemy, player, 1))
        {
            y -= 1;
        }
        else if (howMuch > 25 && this -> CheckDirection(2, wall, enemy, player, 1))
        {
            y += 1;
        }
        this -> CheckCollision(wall, player, enemy, bonus);
    }
}

void Enemy::MoveAI(Wall **wall, Player *player, Enemy **enemy, Bonus **bonus)
{
    short collisionWith=0;
    switch(tempDirection)
    {
    case 0: //right
    {
        direction = 0;

        tempX = x;
        x += TANK_SPEED;

        if(x > BATTLEFIELD_WIDTH)
            x = tempX;

        collisionWith = this -> CheckCollision(wall, player, enemy, bonus);

        if(collisionWith > 0)
            colision = true;
        else
            colision = false;

        if(collisionWith == 3 || collisionWith == 1)
        {
            short howMuch=0;
            if(y % TANK_SIZE != 0 )
            {
                howMuch = y % TANK_SIZE ;
                if(howMuch <= 25 && this -> CheckDirection(3, wall, enemy, player, 1))
                    y -= 2;
                else if (howMuch > 25 && this -> CheckDirection(2, wall, enemy, player, 1))
                    y += 2;

                this -> CheckCollision(wall, player, enemy, bonus);
            }

            if (collisionWith == 3) //destroyable wall
            {
                if(this -> CheckAimWall(wall, enemy))
                {
                    tarGetAhead = true;
                    stop = true;
                }
            }
        }
        else if (collisionWith == 4) //player
        {
            if(this -> CheckAimPlayer(player, enemy, wall))
            {
                attack = false;
                tarGetAhead = true;
            }
            else
                attack = true;
        }
        else
        {
            if(this -> CheckAimPlayer(player, enemy, wall))
                tarGetAhead = true;
            else if(this -> CheckAimWall(wall, enemy))
                tarGetAhead = true;
        }

        break;
    }
    case 1://left
    {
        direction = 1;

        tempX = x;
        x -= TANK_SPEED;
        if(x < 0)
            x = tempX;

        collisionWith = this -> CheckCollision(wall, player, enemy, bonus);

        if(collisionWith > 0)
            colision = true;
        else
            colision = false;

        if(collisionWith == 3 || collisionWith == 1)
        {
            short howMuch=0;

            if(y % TANK_SIZE != 0 )
            {
                howMuch = y % TANK_SIZE ;
                if(howMuch <= 25 && this -> CheckDirection(3, wall, enemy, player, 1))
                    y -= 2;
                else if (howMuch > 25 && this -> CheckDirection(2, wall, enemy, player, 1))
                    y += 2;

                this -> CheckCollision(wall, player, enemy, bonus);
            }
            if (collisionWith == 3) //destroyable wall
            {
                if(this -> CheckAimWall(wall, enemy))
                {
                    tarGetAhead = true;
                }
            }
        }
        else if (collisionWith == 4) //player
        {
            if(this -> CheckAimPlayer(player, enemy, wall))
            {
                attack =false;
                tarGetAhead = true;
            }
            else
                attack = true;
        }
        else
        {
            if(this -> CheckAimPlayer(player, enemy, wall))
                tarGetAhead = true;

            else if(this -> CheckAimWall(wall, enemy))
                tarGetAhead = true;

        }
        break;
    }
    case 2: //dol
    {
        direction = 2;

        tempY = y;
        y += TANK_SPEED;
        if(y > BATTLEFIELD_HEIGHT)
            y = tempY;

        collisionWith = this -> CheckCollision(wall, player, enemy, bonus);

        if(collisionWith > 0)
            colision = true;
        else
            colision = false;

        if(collisionWith == 3 || collisionWith == 1)
        {
            short howMuch=0;
            if(x % TANK_SIZE != 0)
            {
                howMuch = x % TANK_SIZE ;
                if(howMuch <= 25 && this -> CheckDirection(1, wall, enemy, player, 1))
                    x -= 2;
                else if (howMuch > 25 && this -> CheckDirection(0, wall, enemy, player, 1))
                    x += 2;

                this -> CheckCollision(wall, player, enemy, bonus);
            }
            if (collisionWith == 3) //destroyable wall
            {
                if(this -> CheckAimWall(wall, enemy))
                {
                    tarGetAhead = true;
                }
            }
        }
        else if (collisionWith == 4) //player
        {

            if(this -> CheckAimPlayer(player, enemy, wall))
            {
                attack =false;
                tarGetAhead = true;
            }
            else
                attack = true;
        }
        else
        {
            if(this -> CheckAimPlayer(player, enemy, wall))
                tarGetAhead = true;

            else if(this -> CheckAimWall(wall, enemy))
                tarGetAhead = true;
        }
        break;
    }
    case 3: //gora
    {
        direction = 3;

        tempY = y;
        y -= TANK_SPEED;
        if(y < 0)
            y = tempY;


        collisionWith = this -> CheckCollision(wall, player, enemy, bonus);

        if(collisionWith > 0)
            colision = true;
        else
            colision = false;

        if(collisionWith == 3 || collisionWith == 1)
        {
            short howMuch=0;
            if(x % TANK_SIZE != 0)
            {
                howMuch = x % TANK_SIZE ;
                if(howMuch <= 25 && this -> CheckDirection(1, wall, enemy, player, 1))
                    x -= 2;
                else if (howMuch > 25 && this -> CheckDirection(0, wall, enemy, player, 1))
                    x += 2;

                this -> CheckCollision(wall, player, enemy, bonus);
            }
            if (collisionWith == 3) //destroyable wall
            {
                if(this -> CheckAimWall(wall, enemy))
                {
                    tarGetAhead = true;
                }
            }
        }
        else if (collisionWith == 4) //player
        {
            if(this -> CheckAimPlayer(player, enemy, wall))
            {
                attack =false;
                tarGetAhead = true;
            }
            else
                attack = true;
        }
        else
        {
            if(this -> CheckAimPlayer(player, enemy, wall))
                tarGetAhead = true;

            else if(this -> CheckAimWall(wall, enemy))
                tarGetAhead = true;
        }
        break;
    }
    }
}

void Enemy::EnemyAI(Wall **wall, Enemy **enemy, Player *player, Bonus **bonus, Rocket **rocket)
{
    if(!dead && !gameover)
    {
        stop = false;
        tarGetAhead = false;

        short enemyAlive = CheckEnemyAlive(enemy);
        if(enemyAlive == 1 && ((player -> GetLife() > 1 && gameMode != 2) || (enemies - enemiesKilled - enemyAlive > 0 && player -> GetLife() > 1 && enemiesAtOnce > 1) || (Enemy::hasBase && Wall::baseExist && wall[Wall::baseID] -> GetLife() > 1 )) && !attack)
        {
            stop = true;
            if(this -> CheckAimPlayer(player, enemy, wall))
                tarGetAhead = true;
            else if(Enemy::hasBase && this -> CheckAimBase(wall, Wall::baseID, enemy))
                tarGetAhead = true;

            short tempDirectionAI = direction;

            direction = 0;
            if(this -> CheckAimPlayer(player, enemy, wall))
                tarGetAhead = true;
            else
            {
                direction = 1;
                if(this -> CheckAimPlayer(player, enemy, wall))
                    tarGetAhead = true;
                else
                {
                    direction = 2;
                    if(this -> CheckAimPlayer(player, enemy, wall))
                        tarGetAhead = true;
                    else
                    {
                        direction = 3;
                        if(this -> CheckAimPlayer(player, enemy, wall))
                            tarGetAhead = true;
                        else
                            direction = tempDirectionAI;
                    }
                }
            }

            tempDirection = direction;
            firstmovement = false;
        }
        else if((Enemy::hasPlayer == false && Enemy::hasBase == false) || (Enemy::hasPlayer == false && Enemy::attackBase[id] == false))
        {
            if(attack == true)
                attack = false;

            this -> CheckNearbyArea(wall, enemy, player);

            if(Enemy::hasPlayer == true && this -> CheckAimPlayer(player, enemy, wall))
            {
                tarGetAhead = true;
                if(direction > 1 && abs(player -> GetY() - y) < 76)
                    stop = true;
                else if(direction < 2 && abs(player -> GetX() - x) < 76)
                    stop = true;
                else if(canShoot)
                    stop = true;
            }
            else if(this -> CheckAimWall(wall, enemy))
            {
                tarGetAhead = true;
                if(wallAtPath)
                {
                    if(direction > 1 && abs(wall[wallID] -> GetY() - y) < 76)
                        stop = true;
                    else if(direction < 2 && abs(wall[wallID] -> GetX() - x) < 76)
                        stop = true;
                    else if(colision || canShoot)
                        stop = true;
                }
            }

            if(!stop)
            {
                if(!firstmovement)
                {
                    if(this -> SearchForDirection())
                    {
                        tempDirection = this -> EnemyPilot(enemy, wall, player, false);
                        if(tempDirection == 5)
                        {
                            Enemy::isPlayer[destinationX][destinationY] = 4;
                            stop = true;
                        }
                    }
                    else
                        ClearPlayerArray(wall);

                    firstmovement = true;
                }

                if(x == tempDestinationX && tempDestinationY == y)
                {
                    directionCounter = 0;
                    this -> CheckDestination(wall);
                    tempDirection = this -> EnemyPilot(enemy, wall, player, false);
                    if(tempDirection == 5)
                    {
                        stop = true;
                        Enemy::isPlayer[destinationX][destinationY] = 4;
                    }
                }
                else
                {
                    directionCounter ++;

                    this -> MoveCorrection(wall, player, enemy, bonus);

                    if (directionCounter >= 26)
                    {
                        directionCounter = 0;
                        this -> CheckDestination(wall);
                        tempDirection = this -> EnemyPilot(enemy, wall, player, false);
                        if(tempDirection == 5)
                        {
                            stop = true;
                            Enemy::isPlayer[destinationX][destinationY] = 4;
                        }
                    }
                }
            }
        }
        else if(Enemy::hasBase == true && Enemy::attackBase[id] == true)
        {
            this -> CheckNearbyArea(wall, enemy, player);
            SetBaseCoord(enemy,wall, id);

            if(Enemy::hasPlayer == true && this-> CheckAimPlayer(player, enemy, wall))
            {
                tarGetAhead = true;
                if(direction > 1 && abs(player -> GetY() - y) < 76)
                    stop = true;
                else if(direction < 2 && abs(player -> GetX() - x) < 76)
                    stop = true;
                else if(canShoot)
                    stop = true;

                if(attack == true)
                    attack = false;
            }
            else if(this -> CheckAimWall(wall, enemy) && wallAtPath)
            {
                tarGetAhead = true;
                if(wallAtPath)
                {
                    if(direction > 1 && abs(wall[wallID] -> GetY() - y) < 76)
                        stop = true;
                    else if(direction < 2 && abs(wall[wallID] -> GetX() - x) < 76)
                        stop = true;
                    else if(colision || canShoot)
                        stop = true;
                }
            }
            else if(this -> CheckAimBase(wall, Wall::baseID, enemy))
            {
                tarGetAhead = true;

                if(direction > 1 && abs(wall[Wall::baseID] -> GetY() - y) < 76)
                    stop = true;
                else if(direction < 2 && abs(wall[Wall::baseID] -> GetX() - x) < 76)
                    stop = true;
                else if(colision || canShoot)
                    stop = true;
            }

            if(!stop)
            {
                if(!firstmovement)
                {
                    tempDirection = this -> EnemyPilot(enemy, wall, player, false);
                    if(tempDirection == 5)
                        stop = true;

                    firstmovement = true;
                }

                if(x == tempDestinationX && tempDestinationY == y)
                {
                    attack = false;
                    directionCounter = 0;
                    tempDirection = this -> EnemyPilot(enemy, wall, player, false);

                    if(tempDirection == 5)
                        stop = true;
                }
                else
                {
                    directionCounter ++;

                    this -> MoveCorrection(wall, player, enemy, bonus);

                    if (directionCounter >= 26)
                    {
                        directionCounter = 0;

                        tempDirection = this -> EnemyPilot(enemy, wall, player, false);
                        if(tempDirection == 5)
                            stop = true;
                    }
                }
            }
        }
        else if(Enemy::hasPlayer == true)
        {
            this -> CheckNearbyArea(wall, enemy, player);

            if(this -> CheckAimPlayer(player, enemy, wall))
            {
                tarGetAhead = true;
                if(direction > 1 && abs(player -> GetY() - y) < 76)
                    stop = true;
                else if(direction < 2 && abs(player -> GetX() - x) < 76)
                    stop = true;
                else if(canShoot)
                    stop = true;

                if(attack == true)
                    attack = false;
            }
            else if(this -> CheckAimWall(wall, enemy) && wallAtPath)
            {
                tarGetAhead = true;
                if(wallAtPath)
                {
                    if(direction > 1 && abs(wall[wallID] -> GetY() - y) < 76)
                        stop = true;
                    else if(direction < 2 && abs(wall[wallID] -> GetX() - x) < 76)
                        stop = true;
                    else if(colision || canShoot)
                        stop = true;
                }
            }

            if(!stop)
            {
                if(!firstmovement)
                {
                    tempDirection = this -> EnemyPilot(enemy, wall, player, false);
                    if(tempDirection == 5)
                        stop = true;

                    firstmovement = true;
                }

                if(x == tempDestinationX && tempDestinationY == y)
                {
                    attack = false;
                    directionCounter = 0;
                    tempDirection = this -> EnemyPilot(enemy, wall, player, false);

                    short kierunek = direction;

                    direction = 0;
                    if(this -> CheckAimPlayer(player, enemy, wall))
                        stop = true;
                    else
                    {
                        direction = 1;
                        if(this -> CheckAimPlayer(player, enemy, wall))
                            stop = true;
                        else
                        {
                            direction = 2;
                            if(this -> CheckAimPlayer(player, enemy, wall))
                                stop = true;
                            else
                            {
                                direction = 3;
                                if(this -> CheckAimPlayer(player, enemy, wall))
                                    stop = true;
                                else
                                    direction = kierunek;
                            }
                        }
                    }

                    tempDirection = direction;

                    if(abs(x - player -> GetX()) < 112 || abs(y - player -> GetY()) < 112)
                        attack = true;

                    if(tempDirection == 5)
                    {
                        //No stop if enemy can't see player but he try to follow player
                        if(abs(x - player -> GetX()) > 112 || abs(y - player -> GetY()) > 112)
                        {
                            switch(Enemy::playerDirection)
                            {
                            case 0:
                            {
                                destinationX += TANK_SIZE;
                                if( destinationX > BATTLEFIELD_WIDTH)
                                    destinationX = BATTLEFIELD_WIDTH;

                                break;
                            }
                            case 1:
                            {
                                destinationX -= TANK_SIZE;
                                if(destinationX < 0)
                                    destinationX = 0;

                                break;
                            }
                            case 2:
                            {
                                destinationY += TANK_SIZE;
                                if( destinationY > BATTLEFIELD_HEIGHT)
                                    destinationY = BATTLEFIELD_HEIGHT;
                                break;
                            }
                            case 3:
                            {
                                destinationY -= TANK_SIZE;
                                if( destinationY < 0)
                                    destinationY = 0;
                                break;
                            }
                            }

                            if(Enemy::lostPlayerTimer >= 2)
                            {
                                Enemy::lostPlayerTimer = 0;
                                Enemy::hasPlayer = false;
                            }
                            else
                                Enemy::lostPlayerTimer++;
                        }
                        else
                            this -> FightCoord(player, wall, enemy);
                    }
                }
                else
                {
                    directionCounter++;

                    bool canMove = this -> CheckPlayerFuture(tempDirection, player, 2);
                    if(canMove == true)
                        this -> FightCoord(player, wall, enemy);

                    short howNeed=0;
                    if(x % TANK_SIZE != 0 && tempDirection > 1 && !canMove && this -> CheckPlayerFuture(tempDirection, player, 1))
                    {
                        howNeed = x % TANK_SIZE ;
                        if(howNeed <= 25)
                            x -= 1;
                        else
                            x += 1;

                        this -> CheckCollision(wall, player, enemy, bonus);
                    }
                    else if(y % TANK_SIZE != 0 && tempDirection <2 && !canMove && this -> CheckPlayerFuture(tempDirection, player, 1))
                    {
                        howNeed = y % TANK_SIZE ;
                        if(howNeed <= 25)
                            y -= 1;
                        else
                            y += 1;

                        this -> CheckCollision(wall, player, enemy, bonus);
                    }

                    if(canMove == false)
                    {
                        if(x % TANK_SIZE != 0 && tempDirection >1)
                        {
                            howNeed = x % TANK_SIZE ;
                            if(howNeed <= 25)
                                x -= 1;
                            else
                                x += 1;

                            this -> CheckCollision(wall, player, enemy, bonus);
                        }
                        else if(y % TANK_SIZE != 0 && tempDirection <2)
                        {
                            howNeed = y % TANK_SIZE ;
                            if(howNeed <= 25)
                                y -= 1;
                            else
                                y += 1;

                            this -> CheckCollision(wall, player, enemy, bonus);
                        }
                    }

                    if (directionCounter >= 27)
                    {
                        directionCounter = 0;

                        tempDirection = this -> EnemyPilot(enemy, wall, player, false);
                        if(tempDirection == 5)
                            stop = true;
                    }
                }
            }
        }
        else if(!player -> GetActive())
        {
            if(directionCounter == 0)
                tempDirection = this -> EnemyPilot(enemy, wall, player, false);

            this -> MoveCorrection(wall, player, enemy, bonus);

            directionCounter ++;

            if (directionCounter >= 35)
                directionCounter = 0;

            if(this -> CheckAimWall(wall, enemy))
                tarGetAhead = true;
        }

        if(!stop)
            this -> MoveAI(wall, player, enemy, bonus);

        if(canShoot && tarGetAhead)
            this -> Shoot(rocket);
    }
}
