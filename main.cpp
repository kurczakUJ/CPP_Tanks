#include "config.hpp"
#include "allegroconfig.hpp"
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

int main()
{
    InitializeVariables();
    InitializeGame();
    GameMenu();

    return 0;
};
