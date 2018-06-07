#include "rocket.hpp"
#include "config.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "enemy.hpp"
#include "explosion.hpp"
#include "bonus.hpp"
#include "player.hpp"
#include "wall.hpp"
#include "main.hpp"

extern ALLEGRO_SAMPLE *sound[SOUNDS];

extern bool gameover;
extern unsigned short gameMode;
extern short enemiesKilled;
extern bool youDied;
extern bool baseDestroyed;

short Rocket::GetX()
{
    return x;
};

void Rocket::SetX(short _x)
{
    x = _x;
};

short Rocket::GetY()
{
    return y;
};

void Rocket::SetY(short _y)
{
    y = _y;
};

short Rocket::GetDirection()
{
    return direction;
};

void Rocket::SetDirection(short _direction)
{
    direction = _direction;
};

bool Rocket::GetTeam()
{
    return team;
};

void Rocket::SetTeam( bool _team)
{
    team = _team;
};

bool Rocket::GetVisible()
{
    return visible;
};

void Rocket::SetVisible( bool _visible)
{
    visible = _visible;
};

short Rocket::GetSpeed()
{
    return speed;
};

void Rocket::SetSpeed( short _speed)
{
    speed = _speed;
};

void Rocket::RocketOff()
{
    if(team == true) //player
    {
        Rocket::rocketsCounter[0]--;
        if(Rocket::rocketsCounter[0] < 0)
            Rocket::rocketsCounter[0] = 0;
    }
    else
    {
        Rocket::rocketsCounter[1]--;
        if(Rocket::rocketsCounter[1] < 0)
            Rocket::rocketsCounter[1] = 0;
    }
};

void Rocket::CreateSmallExplosion(Explosion ** explosion)
{
    short choice=GiveExplosionID(explosion);
    explosion[choice] -> SetX(x);
    explosion[choice] -> SetY(y);

    if(direction == 2)
        explosion[choice] -> SetX(x-5);
    else if(direction == 3)
        explosion[choice] -> SetX(x-10);
    else if (direction == 1 || direction == 0)
        explosion[choice] -> SetY(y-5);

    explosion[choice] -> SetSmall(true);
    explosion[choice] -> SetVisible(true);

    explosion[choice] -> SetLife(SMALL_EXPLOSION_TIME);
    explosion[choice] -> CreateExplosion();
    al_play_sample(sound[4], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

void Rocket::CreateBigExplosion(Explosion ** explosion, short _x, short _y)
{
    short choice=GiveExplosionID(explosion);
    explosion[choice] -> SetX(_x);
    explosion[choice] -> SetY(_y);
    explosion[choice] -> SetSmall(false);
    explosion[choice] -> SetVisible(true);
    explosion[choice] -> SetLife(BIG_EXPLOSION_TIME);
    explosion[choice] -> CreateExplosion();
    al_play_sample(sound[2], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

void Rocket::Move(Rocket ** rocket, Wall ** sciany, Player *player, Enemy ** enemy, Explosion ** explosion, Bonus ** bonus)
{
    this -> CheckColision(rocket, sciany, player, enemy, explosion, bonus);

    bool rocketOff = false;

    if(visible && !gameover)
    {
        switch(direction)
        {
        case 0:
        {
            x += speed;

            if(x > REAL_BATTLEFIELD_WIDTH)
                rocketOff = true;

            break;
        }
        case 1:
        {
            x -= speed;

            if(x < 0)
                rocketOff = true;

            break;
        }
        case 2:
        {
            y += speed;

            if(y > REAL_BATTLEFIELD_HEIGHT)
                rocketOff = true;

            break;
        }
        case 3:
        {
            y -= speed;

            if(y < 0)
                rocketOff = true;

            break;
        }
        }

        if(rocketOff)
        {
            visible = false;
            this -> RocketOff();
            this -> CreateSmallExplosion(explosion);
        }

        this -> CheckColision(rocket, sciany, player, enemy, explosion, bonus);
    }
};

void Rocket::Shoot(Player * player)
{
    Player::ammoTimer = 0;

    switch(player -> GetDirection())
    {
    case 0:
    {
        x = player -> GetX() + 51;
        y = player -> GetY() + 21;
        direction = 0;
        break; //right
    }
    case 1:
    {
        x = player -> GetX() - 16;
        y = player -> GetY() + 21;
        direction = 1;
        break; //left
    }
    case 2:
    {
        x = player -> GetX() + 21;
        y = player -> GetY() + 60;
        direction = 2;
        break; //down
    }
    case 3:
    {
        x = player -> GetX() + 29;
        y = player -> GetY() - 14;
        direction = 3;
        break; //up
    }
    }

    Rocket::rocketsCounter[0]++;
    visible = true;
    team = true;
    speed = player -> GetAmmoSpeed();

    al_play_sample(sound[0], 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
};

void Rocket::HitWall(Wall ** sciany, short choice)
{
    visible = false;
    this -> RocketOff();
    if(sciany[choice] -> GetDestroyable())
    {
        sciany[choice] -> SetLife(sciany[choice] -> GetLife() - 1);
        if(sciany[choice] -> GetLife() == 0)
            sciany[choice] -> SetVisible(false);
    }
}

void Rocket::HitPlayer(Player * player)
{
    visible = false;
    player -> SetLife(player -> GetLife() - 1);

    //simulate damage
    if(player -> GetShoots() > 1)
        player -> SetShoots(player -> GetShoots() - 1);
    else if(player -> GetAmmoSpeed() > AMMO_SPEED - 1)
        player -> SetAmmoSpeed(player -> GetAmmoSpeed() - 1);
    else if(player -> GetAmmoTimer() < 60)
        player -> SetAmmoSpeed(player -> GetAmmoSpeed() + 10);

    this -> RocketOff();
}

void Rocket::HitEnemy(Enemy ** enemy, Player * player, short choice)
{
    visible = false;
    enemy[choice] -> SetLife(enemy[choice] -> GetLife() - 1);

    if(enemy[choice] -> GetLife() == 0 )
    {
        enemy[choice] -> SetDead(true);
        enemy[choice] -> SetRespawnDelayTimer(1); //1 to start counting
        if(this -> GetTeam())
        {
            player -> SetPoints(player -> GetPoints() +((enemy[choice] -> GetDifficulty()+1) * POINTS_FOR_KILL ));
            player -> SetKills(player -> GetKills() + 1);
        }
    }

    this -> RocketOff();
}

void Rocket::HitRocket(Rocket ** rocket, short choice)
{
    visible = false;
    rocket[choice] -> SetVisible(false);
    this -> RocketOff();
    rocket[choice] -> RocketOff();
}

void Rocket::CheckColision(Rocket ** rocket, Wall ** sciany, Player *player, Enemy ** enemy, Explosion ** explosion, Bonus ** bonus)
{
    bool hit=false; //only one Hit
    for (short i=0; i < OBSTACLES; i++)
    {
        if(sciany[i] -> GetVisible())
        {
            switch(direction)
            {
            case 0:
            {
                if(x + ROCKET_X >= sciany[i] -> GetX() && x <= sciany[i] -> GetX() + OBSTACLE_SIZE  && y >= sciany[i] -> GetY() - ROCKET_Y  && y <= sciany[i] -> GetY() +OBSTACLE_SIZE)
                    hit=true;

                break;
            }
            case 1:
            {
                if(x >= sciany[i] -> GetX() && x <= sciany[i] -> GetX() +OBSTACLE_SIZE && y >= sciany[i] -> GetY() - ROCKET_Y  && y <= sciany[i] -> GetY() +OBSTACLE_SIZE)
                    hit=true;

                break;
            }
            case 2:
            {
                if(x >= sciany[i] -> GetX() - ROCKET_Y && x <= sciany[i] -> GetX() + OBSTACLE_SIZE && y + ROCKET_X >= sciany[i] -> GetY() && y + ROCKET_X <= sciany[i] -> GetY() +OBSTACLE_SIZE)
                    hit=true;

                break;
            }
            case 3:
            {
                if(x + ROCKET_Y >= sciany[i] -> GetX() && x - ROCKET_Y <= sciany[i] -> GetX() + OBSTACLE_SIZE && y <= sciany[i] -> GetY() + OBSTACLE_SIZE && y >= sciany[i] -> GetY())
                    hit=true;

                break;
            }
            }

            if(hit)
                this -> HitWall(sciany, i);

            if(!sciany[i] -> GetVisible())
            {
                this -> CreateBigExplosion(explosion, sciany[i] -> GetX(), sciany[i] -> GetY());

                if(sciany[i] -> GetBase())
                {
                    if(!baseDestroyed && !youDied)
                        baseDestroyed = true;

                    Enemy::hasBase = false;
                }


                ModeGuardian();
            }
            else if(hit && sciany[i] -> GetVisible())
                this -> CreateSmallExplosion(explosion);

            if(hit)
                return;
        }
    }

    if(player -> GetActive())
    {
        switch(direction)
        {
        case 0:
        {
            if(x + ROCKET_X >= player -> GetX() && x <= player -> GetX() + TANK_SIZE  && y >= player -> GetY() - ROCKET_Y  && y <= player -> GetY() +TANK_SIZE)
                hit=true;

            break;
        }
        case 1:
        {
            if(x >= player -> GetX() && x <= player -> GetX() +TANK_SIZE && y >= player -> GetY() - ROCKET_Y  && y <= player -> GetY() +TANK_SIZE)
                hit=true;

            break;
        }
        case 2:
        {
            if(x >= player -> GetX() - ROCKET_Y && x <= player -> GetX() + TANK_SIZE && y + ROCKET_X >= player -> GetY() && y + ROCKET_X <= player -> GetY() +TANK_SIZE)
                hit=true;

            break;
        }
        case 3:
        {
            if(x + ROCKET_Y >= player -> GetX() && x - ROCKET_Y <= player -> GetX() + TANK_SIZE && y <= player -> GetY() + TANK_SIZE && y >= player -> GetY())
                hit=true;

            break;
        }
        }

        if(hit)
        {
            this -> HitPlayer(player);

            if(player -> GetLife() == 0)
            {
                this -> CreateBigExplosion(explosion, player -> GetX(), player -> GetY());
                if(!youDied && !youDied)
                    youDied = true;

                player -> SetActive(false);
                Enemy::hasPlayer = false;
                ClearPlayerArray(sciany);
            }
            else if(player -> GetLife() != 0)
            {
                this -> CreateSmallExplosion(explosion);
            }

            return;
        }
    }

    for(short h = 0; h < ENEMIES; h++)
    {
        if(!enemy[h] -> GetDead())
        {
            switch(direction)
            {
            case 0:
            {
                if(x + ROCKET_X >= enemy[h] -> GetX() && x <= enemy[h] -> GetX() + TANK_SIZE  && y >= enemy[h] -> GetY() - ROCKET_Y  && y <= enemy[h] -> GetY() +TANK_SIZE)
                    hit=true;

                break;
            }
            case 1:
            {
                if(x >= enemy[h] -> GetX() && x <= enemy[h] -> GetX() +TANK_SIZE && y >= enemy[h] -> GetY() - ROCKET_Y  && y <= enemy[h] -> GetY() +TANK_SIZE)
                    hit=true;

                break;
            }
            case 2:
            {
                if(x >= enemy[h] -> GetX() - ROCKET_Y && x <= enemy[h] -> GetX() + TANK_SIZE && y + ROCKET_X >= enemy[h] -> GetY() && y + ROCKET_X <= enemy[h] -> GetY() +TANK_SIZE)
                    hit=true;

                break;
            }
            case 3:
            {
                if(x + ROCKET_Y >= enemy[h] -> GetX() && x - ROCKET_Y <= enemy[h] -> GetX() + TANK_SIZE && y <= enemy[h] -> GetY() + TANK_SIZE && y >= enemy[h] -> GetY())
                    hit=true;

                break;
            }
            }

            if(hit)
                this -> HitEnemy(enemy, player, h);

            if(enemy[h] -> GetDead())
            {
                this -> CreateBigExplosion(explosion, enemy[h] -> GetX(), enemy[h] -> GetY());

                if(rand()%100 < BONUS_CHANCE)
                {
                    short choice=GiveBonusID(bonus);
                    bonus[choice] -> SetX(enemy[h] -> GetX());
                    bonus[choice] -> SetY(enemy[h] -> GetY());
                    bonus[choice] -> SetVisible(true);
                }

                if(gameMode == 2)
                    enemiesKilled++;

                ModeGuardian();
            }
            else if(hit && !enemy[h] -> GetDead())
            {
                this -> CreateSmallExplosion(explosion);

                short playerDirection = 0; //turn around if enemy Get Hitted by rocket

                if (direction == 1 || direction == 3)
                    playerDirection = direction - 1;
                else if(direction == 0 || direction == 2)
                    playerDirection = direction + 1;

                if(enemy[h] -> GetDirection() != playerDirection)
                {
                    enemy[h] -> SetTempDirection(playerDirection);
                    enemy[h] -> SetDirection(playerDirection);
                    enemy[h] -> SetDirectionCounter(1);
                    enemy[h] -> SetTarGetAhead(true);
                }
                else
                    enemy[h] -> SetTarGetAhead(true);
            }

            if(hit)
                return;
        }
    }

    for(short h = 0; h < ROCKETS; h++)
    {
        if(rocket[h] -> GetVisible() && rocket[h] != this && rocket[h] -> GetX() > 0 && rocket[h] -> GetY() > 0)
        {
            switch(direction)
            {
            case 0:
            {
                //1 horizontal rocket
                //2 vertical rocket

                if(rocket[h] -> GetDirection() < 2)
                {
                    if(x + ROCKET_X >= rocket[h] -> GetX()  && x + ROCKET_X <= rocket[h] -> GetX() + ROCKET_X )
                        if((y >= rocket[h] -> GetY() && y <= rocket[h] -> GetY() + ROCKET_Y) || (y <= rocket[h] -> GetY() && y + ROCKET_Y >= rocket[h] -> GetY()))
                            hit=true;
                }
                else
                {
                    if(x + ROCKET_X >= rocket[h] -> GetX()  && x + ROCKET_X <= rocket[h] -> GetX() + ROCKET_Y )
                        if((y >= rocket[h] -> GetY() && y <= rocket[h] -> GetY() + ROCKET_X) || (y <= rocket[h] -> GetY() && y + ROCKET_Y >= rocket[h] -> GetY()))
                            hit=true;
                }

                break;
            }
            case 1:
            {
                if(rocket[h] -> GetDirection() < 2)
                {
                    if(x + ROCKET_X <= rocket[h] -> GetX() + ROCKET_X && x >= rocket[h] -> GetX() )
                        if((y >= rocket[h] -> GetY() && y <= rocket[h] -> GetY() + ROCKET_Y) || (y <= rocket[h] -> GetY() && y + ROCKET_Y >= rocket[h] -> GetY()))
                            hit=true;
                }
                else
                {
                    if(x <= rocket[h] -> GetX() + ROCKET_Y && x >= rocket[h] -> GetX())
                        if((y >= rocket[h] -> GetY() && y <= rocket[h] -> GetY() + ROCKET_X) || (y <= rocket[h] -> GetY() && y + ROCKET_Y >= rocket[h] -> GetY()))
                            hit=true;
                }
                break;
            }
            case 2:
            {
                if(rocket[h] -> GetDirection() < 2)
                {
                    if(y + ROCKET_X >= rocket[h] -> GetY()  && y + ROCKET_X <= rocket[h] -> GetY() + ROCKET_Y )
                        if((x >= rocket[h] -> GetX() && x <= rocket[h] -> GetX() + ROCKET_X) || (x <= rocket[h] -> GetX() && x + ROCKET_Y >= rocket[h] -> GetX()))
                            hit=true;
                }
                else
                {
                    if(y + ROCKET_X >= rocket[h] -> GetY()  && y + ROCKET_X <= rocket[h] -> GetY() + ROCKET_X )
                        if((x >= rocket[h] -> GetX() && x <= rocket[h] -> GetX() + ROCKET_Y) || (x <= rocket[h] -> GetX() && x + ROCKET_Y >= rocket[h] -> GetX()))
                            hit=true;
                }
                break;
            }
            case 3:
            {
                if(rocket[h] -> GetDirection() < 2)
                {
                    if(y <= rocket[h] -> GetY() + ROCKET_Y && y >= rocket[h] -> GetY() )
                        if((x >= rocket[h] -> GetX() && x <= rocket[h] -> GetX() + ROCKET_X) || (x <= rocket[h] -> GetX() && x + ROCKET_Y >= rocket[h] -> GetX()))
                            hit=true;
                }
                else
                {
                    if(y + ROCKET_X <= rocket[h] -> GetY()  && y >= rocket[h] -> GetY() )
                        if((x >= rocket[h] -> GetX() && x <= rocket[h] -> GetX() + ROCKET_Y) || (x <= rocket[h] -> GetX() && x + ROCKET_Y >= rocket[h] -> GetX()))
                            hit=true;
                }
                break;
            }
            }

            if(hit)
            {
                this -> HitRocket(rocket, h);
                this -> CreateSmallExplosion(explosion);
                return;
            }
        }
    }
};

short GiveRocketID(Rocket **rocket)
{
    for(short i=0; i<ROCKETS; i++)
    {
        if(!rocket[i]->GetVisible())
        {
            return i;
        }
    }
    return 0;
};

void ClearRocket(Rocket ** rocket)
{
    Player::ammoTimer = 0;

    for(short i=0; i<ROCKETS; i++)
    {
        rocket[i] -> SetX(0);
        rocket[i] -> SetY(0);
        rocket[i] -> SetDirection(0);
        rocket[i] -> SetVisible(false);
        rocket[i] -> SetTeam(true);
        rocket[i] -> SetSpeed(0);
    }

    Rocket::rocketsCounter[0] = 0;
    Rocket::rocketsCounter[1] = 0;
}
