#include "bonus.hpp"
#include "explosion.hpp"
#include "wall.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "rocket.hpp"
#include "config.hpp"
#include "allegroconfig.hpp"
#include "menu.hpp"
#include "main.hpp"
#include "aStar.hpp"
#include <stdio.h>
#include <cstdlib>
#include <string>

extern ALLEGRO_SAMPLE *sound[SOUNDS];
extern ALLEGRO_KEYBOARD_STATE keyboard;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *playerTank;
extern ALLEGRO_BITMAP *enemyNormalTank;
extern ALLEGRO_BITMAP *enemyFastTank;
extern ALLEGRO_BITMAP *enemyMidTank;
extern ALLEGRO_BITMAP *enemyHeavyTank;
extern ALLEGRO_BITMAP *ammoBitmap;
extern ALLEGRO_BITMAP *wallBitmap;
extern ALLEGRO_BITMAP *immortalWallBitmap;
extern ALLEGRO_BITMAP *explosionBitmap;
extern ALLEGRO_BITMAP *smallExplosionBitmap;
extern ALLEGRO_BITMAP *baseBitmap;
extern ALLEGRO_BITMAP *baseDamageBitmap;
extern ALLEGRO_BITMAP *bonusBitmap;
extern ALLEGRO_BITMAP *background;
extern ALLEGRO_FONT * font30;
extern ALLEGRO_FONT * font60;
extern ALLEGRO_FONT * hudFont;
extern ALLEGRO_FONT * pauseFont;
extern ALLEGRO_FONT * campaignFont;
extern ALLEGRO_CONFIG* iniFile;

ALLEGRO_BITMAP *enemyTankBitmap = NULL;
ALLEGRO_TIMER *FPSTimer = NULL;
ALLEGRO_THREAD *FPSThread = NULL;

Player * player = new Player;
Enemy ** enemy = new Enemy*[ENEMIES];
Bonus ** bonus = new Bonus*[BONUSES];
Explosion ** explosion = new Explosion*[EXPLOSIONS];
Wall ** wall = new Wall*[OBSTACLES];
Rocket ** rocket = new Rocket*[ROCKETS];
Player * playerCampaign = new Player;

volatile short FPS=0;
volatile short FPS1s=0;
unsigned short gameMode = 0;
bool gameover=false;
bool pause = false;

unsigned short Player::ammoTimer = 0;
uint8_t Enemy::isPlayer[REAL_BATTLEFIELD_WIDTH+TANK_SIZE+1][REAL_BATTLEFIELD_HEIGHT+TANK_SIZE+1];
bool Enemy::hasPlayer = false;
bool Enemy::hasBase = false;
short Enemy::baseCoord[2] = {0};
short Rocket::rocketsCounter[2] = {0};
short Wall::baseID = 0;
bool Wall::baseExist = false;
short Wall::respawnTimer = 0;
short Enemy::playerTimer = 0;
short Enemy::playerDirection = 5;
bool Enemy::attackBase[3] = {0};
short Enemy::lostPlayerTimer = 0;

short levels = 0;
short currentLevel = 0;
short enemiesAtOnce = 0;
short enemies = 0;
short enemiesKilled = 0;

bool levelComplete = false;
bool campaignFinish = false;
bool youDied = false;
bool baseDestroyed = false;
short counterComunicat = 0;

void RandomBonus()
{
    short number=rand()%100;
    if(Wall::baseExist)
    {
        if(number <= 18)
        {
            if(player -> GetShoots() < 4)
                player -> SetShoots(player -> GetShoots() + 1);
        }
        else if(number >= 19 && number <= 39)
        {
            player -> SetLife(player -> GetLife() + 1);
        }
        else if(number >= 40 && number <= 52)
        {
            if(player -> GetAmmoSpeed() < 1 + AMMO_SPEED)
                player -> SetAmmoSpeed(player -> GetAmmoSpeed() + 1);
        }
        else if(number >= 53 && number <= 70)
        {
            Airstrike(enemy, explosion, bonus, player);
        }
        else if(number >= 71 && number <= 86)
        {
            wall[Wall::baseID] -> SetLife(wall[Wall::baseID] -> GetLife() + 1);
        }
        else if(number >= 87)
        {
            if(player -> GetAmmoTimer() > 30)
                player -> SetAmmoTimer(player -> GetAmmoTimer() - 10);
        }
    }
    else
    {
        if(number <= 20)
        {
            if(player -> GetShoots() < 4)
                player -> SetShoots(player -> GetShoots() + 1);
        }
        else if(number >= 21 && number <= 40)
        {
            player -> SetLife(player -> GetLife() + 1);
        }
        else if(number >= 41 && number <= 54)
        {
            if(player -> GetAmmoSpeed() < 1 + AMMO_SPEED)
                player -> SetAmmoSpeed(player -> GetAmmoSpeed() + 1);
        }
        else if(number >= 55 && number <= 79)
        {
            Airstrike(enemy, explosion, bonus, player);
        }
        else if(number >= 80)
        {
            if(player -> GetAmmoTimer() > 30)
                player -> SetAmmoTimer(player -> GetAmmoTimer() - 10);
        }
    }
};

void CampaignMapCreate()
{
    if(levels == 0)
    {
        iniFile = al_load_config_file("level1.tank");
        if(!iniFile)
            ShowError("level1.tank", 0);

        levels = atoi(al_get_config_value(iniFile, "options", "levels"));
        if(levels == 0)
            ShowError("error", 3);

        al_destroy_config(iniFile);
    }
    enemiesKilled = 0;
    currentLevel ++;
    player -> CampaingInitialize(currentLevel);
    WallCampaingInitialize(wall, player, enemy, currentLevel, false);
    EnemycampaingInitialize(enemy, currentLevel, wall, player);
}

void Play()
{
    if(DEBUG && gameMode != 2)
    {
        player -> Initialize(200,500,15,2,1,AMMO_SPEED - 1, 0, 1, 30);

        short choice = GiveWallID(wall);
        wall[choice] -> Create(wall, player, enemy, 300,50,true,2,false);
        if(gameMode == 1)
            wall[choice+1] -> Create(wall, player, enemy, 300,100,true,3,true);

        wall[choice+2] -> Create(wall, player, enemy, 300,150,true,2,false);
        wall[choice+3] -> Create(wall, player, enemy, 300,200,true,2,false);
        wall[choice+4] -> Create(wall, player, enemy, 300,250,true,2,false);
        wall[choice+5] -> Create(wall, player, enemy, 300,300,true,2,false);
        wall[choice+6] -> Create(wall, player, enemy, 300,350,true,2,false);
        wall[choice+7] -> Create(wall, player, enemy, 300,400,true,2,false);
        wall[choice+8] -> Create(wall, player, enemy, 300,450,true,2,false);
        wall[choice+9] -> Create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+10] -> Create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+11] -> Create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+12] -> Create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+13] -> Create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+14] -> Create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+21] -> Create(wall, player, enemy, 200,400,false,2,false);

        for(short i=1 ; i<8 ; i++)
            wall[choice+21+i] -> Create(wall, player, enemy, 100,100,false,2,false);

        enemy[0] -> Spawn(450,50,2,AMMO_SPEED, 0, 80, 0, wall, player, enemy);
        enemy[1] -> Spawn(800,500,2,AMMO_SPEED, 0,80, 1, wall, player, enemy);
    }
    else if(!DEBUG && gameMode == 0)
    {
        player -> Initialize(10,10,10,1,0,AMMO_SPEED - 1, 0, 0, 60);
        enemy[0] -> Spawn(500,50,2,AMMO_SPEED, 0, 80, 0, wall, player, enemy);
        enemy[1] -> Spawn(500,500,2,AMMO_SPEED + 1, 1,50, 2, wall, player, enemy);
        enemy[2] -> Spawn(700,350,2,AMMO_SPEED, 0,60, 1, wall, player, enemy);

        short choice = GiveWallID(wall);
        for(short i=1 ; i<30 ; i++)
            wall[choice+i] -> Create(wall, player, enemy, 100,100,true,2,false);

        choice = GiveWallID(wall);
        for(short i=1 ; i<10 ; i++)
            wall[choice+i] -> Create(wall, player, enemy, 100,100,false,2,false);

    }
    else if(!DEBUG && gameMode == 1)
    {
        player -> Initialize(10,10,10,1,0,AMMO_SPEED - 1, 0, 0, 60);
        enemy[0] -> Spawn(500,50,2,AMMO_SPEED, 0, 80, 0, wall, player, enemy);
        enemy[1] -> Spawn(500,500,2,AMMO_SPEED + 1, 1,50, 2, wall, player, enemy);
        enemy[2] -> Spawn(700,350,3,AMMO_SPEED, 0,60, 1, wall, player, enemy);

        short choice = GiveWallID(wall);
        wall[choice] -> Create(wall, player, enemy, 0,300,true,3,true);
        wall[choice+1] -> Create(wall, player, enemy, 0,250,true,2,false);
        wall[choice+2] -> Create(wall, player, enemy, 50,250,true,2,false);
        wall[choice+3] -> Create(wall, player, enemy, 50,300,true,2,false);
        wall[choice+4] -> Create(wall, player, enemy, 50,350,true,2,false);
        wall[choice+5] -> Create(wall, player, enemy, 0,350,true,2,false);
        choice = GiveWallID(wall);
        for(short i=1 ; i<35 ; i++)
            wall[choice+i] -> Create(wall, player, enemy, 100,100,true,2,false);

        choice = GiveWallID(wall);
        for(short i=1 ; i<10 ; i++)
            wall[choice+i] -> Create(wall, player, enemy, 100,100,false,2,false);
    }

    if(gameMode == 2)
        CampaignMapCreate();

    SetBaseID(wall);
    SetImmortallWallsVisible(wall);

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT ev;
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(FPSTimer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(FPSTimer);
    while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE) && !gameover)
    {
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE && pause )
                break;

            if(ev.keyboard.keycode == ALLEGRO_KEY_P && pause && counterComunicat == 0)
            {
                pause = false;
                al_flush_event_queue(event_queue);
                al_start_timer(FPSTimer);
            }
            else if(ev.keyboard.keycode == ALLEGRO_KEY_P && !pause && counterComunicat == 0)
            {
                pause = true;
                al_stop_timer(FPSTimer);
                al_flush_event_queue(event_queue);
                al_draw_textf( pauseFont, al_map_rgb(255,255,255), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "PAUSED");
                al_flip_display();
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_R && DEBUG)
            {
                Airstrike(enemy, explosion, bonus, player);
            }
        }

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_get_keyboard_state(&keyboard);

            al_clear_to_color(al_map_rgb( 0, 0, 0));
            al_draw_bitmap (background, 960, 0, 0);
            al_draw_textf( hudFont, HUD_COLOR, 1120, 60, ALLEGRO_ALIGN_CENTER, "Points: %i",player -> GetPoints());
            al_draw_textf( hudFont, HUD_COLOR, 1120, 110, ALLEGRO_ALIGN_CENTER, "Kills: %i",player -> GetKills());
            al_draw_textf( hudFont, HUD_COLOR, 1120, 160, ALLEGRO_ALIGN_CENTER, "Lifes: %i",player -> GetLife());
            al_draw_textf( hudFont, HUD_COLOR, 1120, 210, ALLEGRO_ALIGN_CENTER, "Ammo Speed: %i / 3",player -> GetAmmoSpeed() - AMMO_SPEED + 2);
            al_draw_textf( hudFont, HUD_COLOR, 1120, 260, ALLEGRO_ALIGN_CENTER, "Rockets: %i / 4",player -> GetShoots());
            al_draw_textf( hudFont, HUD_COLOR, 1120, 310, ALLEGRO_ALIGN_CENTER, "Reload Speed: %i",player -> GetAmmoTimer());

            if(Wall::baseExist == true && gameMode != 2)
                al_draw_textf( hudFont, HUD_COLOR, 1120, 360, ALLEGRO_ALIGN_CENTER, "Base: %i",wall[Wall::baseID] -> GetLife());
            else if(gameMode == 2 && Wall::baseExist == false)
            {
                al_draw_textf( hudFont, HUD_COLOR, 1120, 10, ALLEGRO_ALIGN_CENTER, "Level: %i/%i",currentLevel, levels);
                al_draw_textf( hudFont, HUD_COLOR, 1120, 360, ALLEGRO_ALIGN_CENTER, "Progress: %i/%i",enemiesKilled, enemies);
            }
            else if(gameMode == 2 && Wall::baseExist == true)
            {
                al_draw_textf( hudFont, HUD_COLOR, 1120, 360, ALLEGRO_ALIGN_CENTER, "Base: %i",wall[Wall::baseID] -> GetLife());
                al_draw_textf( hudFont, HUD_COLOR, 1120, 10, ALLEGRO_ALIGN_CENTER, "Level: %i/%i",currentLevel, levels);
                al_draw_textf( hudFont, HUD_COLOR, 1120, 410, ALLEGRO_ALIGN_CENTER, "Progress: %i/%i",enemiesKilled, enemies);
            }

            if(DEBUG)
            {
                al_draw_textf( font30, HUD_COLOR, 1110, 510, ALLEGRO_ALIGN_CENTER, "TarGet %i x %i, Dest %i x %i",enemy[0] -> GetDestinationX(),   enemy[0] -> GetDestinationY(), enemy[0] -> GetTempDestinationX(), enemy[0] -> GetTempDestinationY());
                al_draw_textf( font30, HUD_COLOR, 1100, 540, ALLEGRO_ALIGN_CENTER, "E0 %i x %i D %i BASE: %i",enemy[0] -> GetX(),   enemy[0] -> GetY(), enemy[0] -> GetTempDirection(), Enemy::attackBase[0]);
                al_draw_textf( font30, HUD_COLOR, 1100, 570, ALLEGRO_ALIGN_CENTER, "Player %i x %i See %s",player -> GetX(),   player -> GetY(), Enemy::hasPlayer ? "true" : "false");
                if(Wall::baseExist == true)
                    al_draw_textf( font30, HUD_COLOR, 1100, 600, ALLEGRO_ALIGN_CENTER, "Base %i x %i See %s",wall[Wall::baseID] -> GetX(),   wall[Wall::baseID] -> GetY(), Enemy::hasBase ? "true" : "false");
            }

            for(short t = 0; t < OBSTACLES; t++)
            {
                if(wall[t] -> GetVisible())
                {
                    if(!wall[t] -> GetDestroyable())
                        al_draw_bitmap (wallBitmap,wall[t] -> GetX(),wall[t] -> GetY(),0);
                    else
                    {
                        if(!wall[t] -> GetBase())
                            al_draw_bitmap (immortalWallBitmap,wall[t] -> GetX(),wall[t] -> GetY(),0);
                        else
                        {
                            if(wall[t] -> GetLife() == 1)
                                al_draw_bitmap (baseDamageBitmap,wall[t] -> GetX(),wall[t] -> GetY(),0);
                            else
                                al_draw_bitmap (baseBitmap,wall[t] -> GetX(),wall[t] -> GetY(),0);
                        }
                    }
                }
            }

            for(short t = 0; t < BONUSES; t++)
            {
                if(bonus[t] -> GetVisible())
                    al_draw_bitmap (bonusBitmap,bonus[t] -> GetX(),bonus[t] -> GetY(), 0);
            }

            for(short t = 0; t < EXPLOSIONS; t++)
            {
                if(explosion[t] -> GetVisible())
                {
                    if(explosion[t] -> GetSmall())
                    {
                        short which = explosion[t] -> GetLife() % 4;

                        if(which == 0)
                        {
                            explosion[t] -> SetAnimationWidth(explosion[t] -> GetAnimationWidth() + 1);
                            if(explosion[t] -> GetAnimationWidth() == 4)
                            {
                                explosion[t] -> SetAnimationWidth(0);
                                explosion[t] -> SetAnimationHeight(explosion[t] -> GetAnimationHeight()+ 1);
                            }
                        }

                        al_draw_bitmap_region(smallExplosionBitmap, explosion[t] -> GetAnimationWidth() * SMALL_ANIMATION_SIZE,  explosion[t] -> GetAnimationHeight() * SMALL_ANIMATION_SIZE, SMALL_ANIMATION_SIZE, SMALL_ANIMATION_SIZE, explosion[t] -> GetX(), explosion[t] -> GetY(), 0);
                    }
                    else
                    {
                        short which = explosion[t] -> GetLife() % 4;

                        if(which == 0)
                        {
                            explosion[t] -> SetAnimationWidth(explosion[t] -> GetAnimationWidth() + 1);
                            if(explosion[t] -> GetAnimationWidth() == 4)
                            {
                                explosion[t] -> SetAnimationWidth(0);
                                explosion[t] -> SetAnimationHeight(explosion[t] -> GetAnimationHeight()+ 1);
                            }
                        }

                        al_draw_bitmap_region(explosionBitmap, explosion[t] -> GetAnimationWidth() * BIG_ANIMATION_SIZE,  explosion[t] -> GetAnimationHeight() * BIG_ANIMATION_SIZE, BIG_ANIMATION_SIZE, BIG_ANIMATION_SIZE, explosion[t] -> GetX(), explosion[t] -> GetY(), 0);
                    }

                    explosion[t] -> SetLife(explosion[t] -> GetLife() - 1);

                    if(explosion[t] -> GetLife() == 0)
                    {
                        explosion[t] -> SetVisible(false);
                        explosion[t] -> SetAnimationHeight(0);
                        explosion[t] -> SetAnimationWidth(0);
                    }
                }
            }

            if(player -> GetActive())
            {
                if(al_key_down(&keyboard, ALLEGRO_KEY_RIGHT))
                    player -> Move(0);
                if(al_key_down(&keyboard, ALLEGRO_KEY_LEFT))
                    player -> Move(1);
                if(al_key_down(&keyboard, ALLEGRO_KEY_DOWN))
                    player -> Move(2);
                if(al_key_down(&keyboard, ALLEGRO_KEY_UP))
                    player -> Move(3);

                player -> CheckColision(wall, enemy, bonus);

                switch(player -> GetDirection())
                {
                case 0:
                    al_draw_rotated_bitmap(playerTank, 0, 0,  player -> GetX(), player -> GetY(), 0, ALLEGRO_FLIP_HORIZONTAL);
                    break; //right
                case 1:
                    al_draw_rotated_bitmap(playerTank, 0, 0,  player -> GetX(), player -> GetY(), 0, 0);
                    break; //left
                case 2:
                    al_draw_rotated_bitmap(playerTank, 0, 0,  player -> GetX(), player -> GetY() +50, 3*ALLEGRO_PI/2, 0);
                    break; //down
                case 3:
                    al_draw_rotated_bitmap(playerTank, 0, 0,  player -> GetX() +50, player -> GetY(), ALLEGRO_PI/2, 0);
                    break; //up
                }

                if(al_key_down(&keyboard, ALLEGRO_KEY_SPACE) && Rocket::rocketsCounter[0] < player -> GetShoots() && Player::ammoTimer > player -> GetAmmoTimer())
                {
                    short choice = GiveRocketID(rocket);
                    rocket[choice] -> Shoot(player);
                }
            }

            for(short u = 0; u < ENEMIES; u++)
            {
                if(!enemy[u] -> GetDead())
                {
                    enemy[u] -> EnemyAI(wall, enemy, player, bonus, rocket);
                    if(enemy[u] -> GetDifficulty() == 0)
                        enemyTankBitmap = enemyNormalTank;
                    else if(enemy[u] -> GetDifficulty() == 1)
                        enemyTankBitmap = enemyFastTank;
                    else if(enemy[u] -> GetDifficulty() == 2)
                        enemyTankBitmap = enemyMidTank;
                    else if(enemy[u] -> GetDifficulty() == 3)
                        enemyTankBitmap = enemyHeavyTank;

                    switch(enemy[u] -> GetDirection())
                    {
                    case 0:
                        al_draw_rotated_bitmap(enemyTankBitmap, 0, 0,  enemy[u] -> GetX(), enemy[u] -> GetY(), 0, ALLEGRO_FLIP_HORIZONTAL);
                        break; //right
                    case 1:
                        al_draw_rotated_bitmap(enemyTankBitmap, 0, 0,  enemy[u] -> GetX(), enemy[u] -> GetY(), 0, 0);
                        break; //left
                    case 2:
                        al_draw_rotated_bitmap(enemyTankBitmap, 0, 0,  enemy[u] -> GetX(), enemy[u] -> GetY() +50, 3*ALLEGRO_PI/2, 0);
                        break; //down
                    case 3:
                        al_draw_rotated_bitmap(enemyTankBitmap, 0, 0,  enemy[u] -> GetX() +50, enemy[u] -> GetY(), ALLEGRO_PI/2, 0);
                        break; //up
                    }
                }
            }

            for(short g = 0; g < ROCKETS; g++)
            {
                if(rocket[g] -> GetVisible())
                {
                    rocket[g] -> Move(rocket, wall, player, enemy, explosion, bonus);

                    switch(rocket[g] -> GetDirection())
                    {
                    case 0:
                        al_draw_rotated_bitmap(ammoBitmap, 0, 0,  rocket[g] -> GetX(), rocket[g] -> GetY(), 0, ALLEGRO_FLIP_HORIZONTAL);
                        break;
                    case 1:
                        al_draw_rotated_bitmap(ammoBitmap, 0, 0,  rocket[g] -> GetX(), rocket[g] -> GetY(), 0, 0);
                        break;
                    case 2:
                        al_draw_rotated_bitmap(ammoBitmap, 0, 0,  rocket[g] -> GetX(), rocket[g] -> GetY(), 3*ALLEGRO_PI/2, 0);
                        break;
                    case 3:
                        al_draw_rotated_bitmap(ammoBitmap, 0, 0,  rocket[g] -> GetX(), rocket[g] -> GetY(), ALLEGRO_PI/2, 0);
                        break;
                    }
                }
            }

            if(levelComplete)
            {
                al_draw_textf( campaignFont, al_map_rgb(255,51,51), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "LEVEL %i COMPLETE", currentLevel);
                counterComunicat++;
            }
            else if(campaignFinish)
            {
                al_draw_textf( campaignFont, al_map_rgb(255,51,51), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "CONGRATULATIONS YOU WON");
                counterComunicat++;
            }
            else if(youDied)
            {
                al_draw_textf( campaignFont, al_map_rgb(255,51,51), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "You Died !");
                counterComunicat++;
            }
            else if(baseDestroyed)
            {
                al_draw_textf( campaignFont, al_map_rgb(255,51,51), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Base was destroyed !");
                counterComunicat++;
            }

            al_flip_display();
            FPS++;

            if(counterComunicat == 2 * FRAMERATE)
            {
                if(levelComplete)
                {
                    *playerCampaign = *player;
                    levelComplete = false;
                    pause = false;
                    al_flush_event_queue(event_queue);
                    al_stop_timer(FPSTimer);
                    al_rest(1.0);
                    ClearVariables();
                    CampaignMapCreate();
                    al_start_timer(FPSTimer);
                }
                if(campaignFinish)
                {
                    al_stop_timer(FPSTimer);
                    pause = false;
                    al_flush_event_queue(event_queue);
                    al_rest(1.0);
                    gameover = true;
                }
                if(youDied || baseDestroyed)
                {
                    al_stop_timer(FPSTimer);
                    pause = false;
                    al_flush_event_queue(event_queue);
                    al_rest(1.0);
                    gameover=true;
                }
            }

            if(Player::ammoTimer <= player -> GetAmmoTimer())
                Player::ammoTimer++;

            for(short u = 0; u < ENEMIES; u++)
            {
                if(enemy[u] -> GetDead())
                {
                    if(enemy[u] -> GetRespawnDelayTimer() == RESPAWN_TIMER)
                    {
                        enemy[u] -> SetRespawnDelayTimer(-1);
                        ModeGuardian();
                    }
                    else if(enemy[u] -> GetRespawnDelayTimer() >= 1)
                        enemy[u] -> SetRespawnDelayTimer(enemy[u] -> GetRespawnDelayTimer() + 1);

                }
                else
                {
                    if(enemy[u] -> GetAmmoTimer() == enemy[u] -> GetAmmoDelay())
                    {
                        enemy[u] -> SetAmmoTimer(-1);
                        enemy[u] -> SetCanShoot(true);
                    }

                    if(enemy[u] -> GetAmmoTimer() >= 1)
                        enemy[u] -> SetAmmoTimer(enemy[u] -> GetAmmoTimer() + 1);
                }
            }

            if(Wall::respawnTimer == RESPAWN_TIMER)
                ModeGuardian();

            if(Wall::respawnTimer >= 1)
                Wall::respawnTimer++;

            if(Enemy::hasPlayer)
                Enemy::playerTimer++;

            if(Enemy::playerTimer == 200)
            {
                Enemy::playerTimer = 0;
                Enemy::hasPlayer = false;
                ClearPlayerArray(wall);
            }

        }
    }
    al_destroy_event_queue(event_queue);
    al_destroy_timer(FPSTimer);

    gameover = true;
};

void ClearVariables()
{
    player -> Clear();
    ClearEnemy(enemy);
    ClearWall(wall);
    ClearRocket(rocket);
    ClearBonus(bonus);
    ClearExplosion(explosion);
    ClearPlayerArray(wall);
    counterComunicat = 0;
    levelComplete = false;
    campaignFinish = false;
    youDied = false;
    baseDestroyed = false;
    SetTarGet(enemy, player);
}

void InitializeVariables()
{
    for (short i = 0; i < BONUSES; i++)
        bonus[i] = new Bonus;

    for (short i = 0; i < EXPLOSIONS; i++)
        explosion[i] = new Explosion;

    for (short i = 0; i < OBSTACLES; i++)
        wall[i] = new Wall;

    for (short i = 0; i < ROCKETS; i++)
        rocket[i] = new Rocket;

    for (short i = 0; i < ENEMIES; i++)
        enemy[i] = new Enemy(i);
}

void InitializeGame()
{
    AllegroInitialize();
    FontsInitialize();
    DataInitialize();
    HighscoreLoad();
    SoundInitialize();
}

void GameMenu()
{
    while(1)
    {
        Menu();

        ClearVariables();
        levels = 0;
        currentLevel = 0;
        gameover = false;
        al_get_keyboard_state(&keyboard);

        FPSTimer = al_create_timer(1.0 / FRAMERATE);
        if(!FPSTimer)
            ShowError("Timer", 1);

        Play();
        HighscoreSave(gameMode, player);
        al_rest(0.4);
    }
}

void ModeGuardian()
{
    switch(gameMode)
    {
    case 0:
    {
        short enemyAlive = CheckEnemyAlive(enemy);
        short wallExist = CheckExistsWalls(wall);

        if(enemyAlive == 0)
            Enemy::hasPlayer = false;

        if(wallExist < 12)
        {
            if(Wall::respawnTimer == RESPAWN_TIMER)
            {
                Wall::respawnTimer = -1;
                for(short i=1 ; i<10 ; i++)
                {
                    short choice = GiveWallID(wall);
                    wall[choice] -> Create(wall, player, enemy, 100,100,true,2,false);
                }
            }
            else if(Wall::respawnTimer <= 0)
                Wall::respawnTimer = 1;
        }

        if(enemyAlive < ENEMY_SIMULTANEOUSLY)
        {
            SetTarGet(enemy, player);
            for(short i=0 ; i<ENEMY_SIMULTANEOUSLY ; i++)
            {
                if(enemy[i] -> GetDead() && enemy[i] -> GetRespawnDelayTimer() == -1)
                {
                    short _x = rand()%400 + 500;
                    short _y = rand()%(BATTLEFIELD_HEIGHT);
                    short _difficulty = rand()%4;
                    switch(_difficulty)
                    {
                    case 0:
                    {
                        enemy[i] -> Spawn(_x,_y, 2, AMMO_SPEED + 1, 1, 80, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 1:
                    {
                        enemy[i] -> Spawn(_x,_y, 3, AMMO_SPEED, 1, 60, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 2:
                    {
                        enemy[i] -> Spawn(_x,_y, 2, AMMO_SPEED + 1, 1, 50, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 3:
                    {
                        enemy[i] -> Spawn(_x,_y, 4, AMMO_SPEED + 1, 1, 60, _difficulty, wall, player, enemy);
                        break;
                    }
                    }
                }
            }
        }
        break;
    }
    case 1:
    {
        short enemyAlive = CheckEnemyAlive(enemy);
        short wallExist = CheckExistsWalls(wall);

        if(enemyAlive == 0)
        {
            Enemy::hasPlayer = false;
            Enemy::hasBase = false;
        }

        if(wallExist < 12)
        {
            if(Wall::respawnTimer == RESPAWN_TIMER)
            {
                Wall::respawnTimer = -1;
                for(short i=1 ; i<10 ; i++)
                {
                    short choice = GiveWallID(wall);
                    wall[choice] -> Create(wall, player, enemy, 100,100,true,2,false);
                }
            }
            else if(Wall::respawnTimer <= 0)
                Wall::respawnTimer = 1;
        }
        if(enemyAlive < ENEMY_SIMULTANEOUSLY)
        {
            SetTarGet(enemy, player);
            for(short i=0 ; i<ENEMY_SIMULTANEOUSLY ; i++)
            {
                if(enemy[i] -> GetDead() && enemy[i] -> GetRespawnDelayTimer() == -1)
                {
                    short _x = rand()%400 + 500;
                    short _y = rand()%(BATTLEFIELD_HEIGHT);
                    short _difficulty = rand()%4;
                    switch(_difficulty)
                    {
                    case 0:
                    {
                        enemy[i] -> Spawn(_x,_y, 2, AMMO_SPEED, 1, 80, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 1:
                    {
                        enemy[i] -> Spawn(_x,_y, 3, AMMO_SPEED, 1, 60, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 2:
                    {
                        enemy[i] -> Spawn(_x,_y, 2, AMMO_SPEED + 1, 1, 50, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 3:
                    {
                        enemy[i] -> Spawn(_x,_y, 4, AMMO_SPEED + 1, 1, 60, _difficulty, wall, player, enemy);
                        break;
                    }
                    }
                }
            }
        }

        break;
    }
    case 2:
    {
        short enemyAlive = CheckEnemyAlive(enemy);

        if(enemyAlive == 0)
        {
            Enemy::hasPlayer = false;
            if(Wall::baseExist)
                Enemy::hasBase = false;
        }

        if(enemyAlive == 0 && enemies - enemiesKilled == 0)
        {
            if(currentLevel == levels)
            {
                if(!campaignFinish)
                    campaignFinish = true;
            }
            else
            {
                if(!levelComplete)
                    levelComplete = true;
            }
        }

        else if(enemyAlive < enemiesAtOnce && enemies - enemiesKilled - enemyAlive > 0)
        {
            SetTarGet(enemy, player);
            for(short i=0 ; i<ENEMIES ; i++)
            {
                if(enemy[i] -> GetDead() && enemy[i] -> GetRespawnDelayTimer() == -1)
                {
                    EnemyCampaignDrop(enemy, currentLevel, wall, player);
                }
            }
        }
        short wallExist = CheckExistsWalls(wall);
        if(wallExist < 12)
        {
            if(Wall::respawnTimer == RESPAWN_TIMER)
            {
                Wall::respawnTimer = -1;
                WallCampaingInitialize(wall, player, enemy, currentLevel, true);
            }
            else if(Wall::respawnTimer <= 0)
                Wall::respawnTimer = 1;
        }

        break;
    }
    }
}

int main()
{
    InitializeVariables();
    InitializeGame();
    GameMenu();

    return 0;
};
