//#include "framebuffer.h"
#include "framebuffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "GPIO_INIT.h"


#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/noSelectMM.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/startSelectMM.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/quitSelectMM.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/brickClear.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/brickMediumClear.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/brickSmallClear.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/brickMedium.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/brickSmall.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/brick.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/background.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/ship.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/shipClear.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/pawn.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/pawnClear.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/shipBullet.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/shipBulletClear.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/knight.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/knightClear.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/queen.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/queenClear.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/heart.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/heartClear.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/enemyBullet.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/enemyBulletClear.h"

#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/loseNoSelect.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/loseRestartSelect.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/loseQuitSelect.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/winNoSelect.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/winRestartSelect.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/winQuitSelect.h"

//Digits
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/zeroDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/oneDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/twoDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/threeDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/fourDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/fiveDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/sixDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/sevenDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/eightDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/nineDigit.h"
#include "/home/pi/Desktop/CPSC359/SpaceInvaders/ObjectsPixelInformation/clearDigit.h"




/** Structures declarations
 */
struct GameState{
	int score;
	int gameOn;
};
struct Pixel{
	int color,x,y;
};

struct replacementBricks{
    long long * pMediumBrickColorCodes;
    long long * pMediumBrickClearColorCodes;
    int mediumWidth;
    int mediumHeight;
    long long * pSmallBrickColorCodes;
    long long * pSmallBrickClearColorCodes;
    int smallWidth;
    int smallHeight;
};

struct objInfo{
  int currentX;
  int currentY;
  long long * pColorCodes;
  long long * pClearColorCodes;
  int width;
  int height;
  int health; //0 for dead, 1 for one live 2 for 2 lives 3 for 3 lives, -1 doesnt apply
  int active; //0 for not present, 1 for present
  int exposed; //0 or 1, depending if the object is free too shoot, or is covered by other monsters. -1 if doesn't apply.
  int bulletXCoordinate; //FOR ENEMIES ONLY so pawn,knight,queen, -1 if doesn't apply
  int bulletYCoordinate; //FOR ENEMIES ONLY so pawn,knight,queen, -1 if doesn't apply
  int bulletActive; //FOR ENEMIES ONLY so pawn,knight,queen , -1 if doesn't apply
};

struct allObj{
	struct objInfo mainMenu[3];
	struct objInfo pawns[10];
	struct objInfo knights[5];
	struct objInfo queens[2];
	struct objInfo bricks[3];
	struct objInfo allObjects[15];
	struct GameState state;
	struct replacementBricks smallerBricks;
	struct objInfo hearts[3];
	struct objInfo enemyBullet;
	
};


struct fbs frameBufferStruct;


/** Function declarations
 */
 
void changeObjImage(struct objInfo *info,long long *pixelColorCodesImg,long long *pixelColorCodesClearImg,int w, int h);

void drawPixel(struct Pixel *pixel);
int updateVerLoc(struct Pixel *pixel);
int updateHorLoc(struct Pixel *pixel);
void clearPixel(struct Pixel *pixel);

long long *getPixelArray(int width, int height, const unsigned char *pImg);
int printImage(int xCoordinate,int yCoordinate,long long *pixelColorCodes,int imgHeight,int imgWidth,int boundsEnable);

void moveRight(struct objInfo *info,int d,int speedOfMovement);
void moveLeft(struct objInfo *info,int d,int speedOfMovement);

void moveAllRight(struct objInfo *array,int howManyTimes,int delayAmount,int objCount,int speedOfMovement,struct GameState *game);
void moveAllLeft(struct objInfo *array,int howManyTimes,int delayAmount,int objCount,int speedOfMovement,struct GameState *game);
void moveAllDown(struct objInfo *array, int howManyTimes,int delayAmount,int objCount,int speedOfMovement,struct GameState *game);

void moveDown(struct objInfo *info,int d,int speedOfMovement);
int moveUp(struct objInfo *info, int d,int speedOfMovement);

void playerShoot(struct objInfo *playerInfo,struct objInfo *shipBullet);

void clearImage(struct objInfo *obj,int respectBounds);

void playerBulletAndPawnsCheck(struct objInfo *shipBullet,struct objInfo pawns[],struct GameState *s);
void playerBulletAndKnightsCheck(struct objInfo *shipBullet,struct objInfo knights[],struct GameState *s);
void playerBulletAndQueensCheck(struct objInfo *shipBullet,struct objInfo queens[],struct GameState *s);

void playerBulletAndBricksCheck(struct objInfo *shipBullet,struct objInfo bricks[],struct replacementBricks *b,struct GameState *s);

void enemyShoot(struct objInfo *whoShoots,struct objInfo *bulletInfo,struct GameState *game);
void enemiesBulletAndBricksCheck(struct objInfo *monsterArray,struct objInfo *brickArray, struct GameState *gameState,int monsterCount,struct objInfo *bullet,struct replacementBricks *b);
void enemiesBulletAndPlayerCheck(struct objInfo *monsterArray,struct objInfo *playerShip,struct GameState *gameState,int monsterCount,struct objInfo *bullet);
void queensBulletAndMonsterCheck(struct objInfo *queens,struct objInfo *monster,struct GameState *game,int monsterCount,struct objInfo *bullet);

long random_at_most(long max);
int * convertNumberIntoArray(unsigned int number,int numOfDigits);

/**
 * Threads
 */

void *mainMenuRunner(void *param); 

void *winOrLoseRunner(void *param);
void *winMenuRunner(void *param);
void *loseMenuRunner(void *param);

void *playerKeyListenerRunner(void *param);
 
void *bulletRunner(void *param);

void *monstersMovementRunner(void *param);
void *knightsMovementRunner(void *param);
void *pawnsMovementRunner(void *param);
void *queensMovementRunner(void *param);
void *queen1MovementRunner(void *param);
void *queen2MovementRunner(void *param);

void *playerActionsRunner(void *param);
void *playerBulletCollisionsRunner(void *param);

void *updateExposedStatusRunner(void *param);

void *updateHeartsRunner(void *param);

void *enemiesShootRunner(void *param);
void *pawnShootRunner(void *param);
void *knightShootRunner(void *param);
void *queenShootRunner(void *param);
void *enemiesBulletCollisionsRunner(void *param);

void *scoreDisplayRunner(void *param);

void *restartGameRunner();










