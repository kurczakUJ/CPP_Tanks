#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define DEBUG 0
#define VERSION "Tanks 1.0"

#define FRAMERATE 60

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

#define XSIZE 19 //x possibilities
#define YSIZE 14 //y possibilities
#define DIRECTIONS 4 // number of possible directions to go at any position

#define MENU_BUTTON_WIDTH 500
#define MENU_BUTTON_HEIGHT 70
#define MENU_BUTTON_SPACE 200

#define AMMO_SPEED 4
#define TANK_SPEED 2
#define TANK_SIZE 50

#define PLAYER_TANK "playerTank.png"
#define ENEMY_NORMAL_TANK "enemyNormal.png"
#define ENEMY_FAST_TANK "enemyFast.png"
#define ENEMY_MID_TANK "enemyMid.png"
#define ENEMY_HEAVY_TANK "enemyHeavy.png"
#define AMMO_BITMAP "ammo.png"
#define WALL_BITMAP "immortallObstacle.png"
#define DESTROYABLE_WALL "wall.png"
#define BIG_EXPLOSION "explosion.bmp"
#define SMALL_EXPLOSION "smallExplosion.bmp"
#define BONUS_BITMAP "bonus.png"
#define BASE_BITMAP "base.png"
#define BASE_DESTROY "baseD.png"
#define SURVIVE_BUTTON "surviveButton.png"
#define BASE_DEFENCE_BUTTON "baseDefenceButton.png"
#define CAMPAIGN_BUTTON "campaignButton.png"
#define HIGHSCORE_BUTTON "highscoreButton.png"
#define EXIT_BUTTON "exitButton.png"
#define BACKGROUND_BITMAP "background.png"
#define BACK_BUTTON "backButton.png"
#define OK_BUTTON "okButton.png"

#define WALL_DESTROY_SOUND "wallDestroy.wav"
#define SHOT_SOUND "shot.wav"
#define EXPLOSION_SOUND "explosion.wav"
#define HIT_TANK_SOUND "hitTank.wav"
#define HIT_WALL_SOUND "hitWall.wav"

#define MAIN_FONT "calibri.ttf"
#define HUD_FONT "hudFont.ttf"
#define CAMPAIGN_FONT "campaign.otf"

#define SOUNDS 5


#pragma GCC diagnostic ignored "-Wwrite-strings" //to ignore showError warning which is correct
#endif
