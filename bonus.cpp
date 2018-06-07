#include "bonus.hpp"
#include "config.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "enemy.hpp"
#include "main.hpp"
#include "explosion.hpp"

extern short enemiesKilled;
extern unsigned short gameMode;

extern ALLEGRO_SAMPLE *sound[SOUNDS];

short Bonus::GetX()
{
    return x;
};

void Bonus::SetX( short _x)
{
    x = _x;
};

short Bonus::GetY()
{
    return y;
};

void Bonus::SetY( short _y)
{
    y = _y;
};

bool Bonus::GetVisible()
{
    return visible;
};

void Bonus::SetVisible( bool _visible)
{
    visible = _visible;
};

short GiveBonusID(Bonus ** bonus)
{
    for(short i=0; i < BONUSES; i++)
    {
        if(!bonus[i] -> GetVisible())
            return i;
    }

    return 0;
};

void Airstrike(Enemy ** enemy, Explosion ** explosion, Bonus ** bonus, Player *player)
{
    short alive = CheckEnemyAlive(enemy);

    for(short i = 0; i < ENEMIES; i++)
    {
        if(!enemy[i] -> GetDead())
        {
            enemy[i] -> SetDead(true);
            enemy[i] -> SetRespawnDelayTimer(1); //1 to start counting to respawn

            short choice = GiveExplosionID(explosion);
            explosion[choice] -> SetX(enemy[i] -> GetX());
            explosion[choice] -> SetY(enemy[i] -> GetY());
            explosion[choice] -> SetSmall(false);
            explosion[choice] -> SetVisible(true);
            explosion[choice] -> SetLife(BIG_EXPLOSION_TIME);
            explosion[choice] -> CreateExplosion();

            if(rand()%100 <= BONUS_CHANCE)
            {
                choice = GiveBonusID(bonus);
                bonus[choice] -> SetX(enemy[i] -> GetX());
                bonus[choice] -> SetY(enemy[i] -> GetY());
                bonus[choice] -> SetVisible(true);
            }

            if(gameMode == 2)
                enemiesKilled++;

            player -> SetPoints(player -> GetPoints() +((enemy[i] -> GetDifficulty()+1) * POINTS_FOR_KILL ));
            player -> SetKills(player -> GetKills() + 1);
        }
    }

    if(alive > 0)
    {
        al_play_sample(sound[1], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        ModeGuardian();
    }
};

void ClearBonus(Bonus ** bonus)
{
    for(short i=0; i < BONUSES; i++)
    {
        bonus[i] -> SetX(0);
        bonus[i] -> SetY(0);
        bonus[i] -> SetVisible(false);
    }
}
