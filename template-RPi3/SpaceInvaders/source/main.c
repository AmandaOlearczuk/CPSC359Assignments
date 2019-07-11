#include "Drawing.h"
#include "Movement.h"
#include "CollisionsCheck.h"

#include <math.h>
 	
/** Create restart game thread on user click Restart, after game ends due to winning or losing
 pthread_t restartGameThread;
 pthread_attr_t restartGameThreadAttr;
 pthread_attr_init(&restartGameThreadAttr); 
 pthread_create(&restartGameThread,&restartGameThreadAttr,restartGameRunner,NULL);
 pthread_join(restartGameThread,NULL);
*/
	
int main(){
  
	//Initialize SNES
    
	gpio = gpioPtr();	//Base address
	
	Init_GPIO(LAT,001); //Set GPIO pin 9 (LATCH) to output
	Init_GPIO(DAT,000); //Set GPIO pin 10 (DATA) to input
	Init_GPIO(CLK,001); //Set GPIO pin 11 (CLOCK) to output
	
	frameBufferStruct = initFbInfo(); //Initialize info about screen
	
	 
	/**
	 * Initialize structures of objects - Background, Ship, Pawns (10), Knights(5),Queens(2) , Obstacles(3).
	 */ 
	 
	struct objInfo mainMenuInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(noSelectMM.width,noSelectMM.height,noSelectMM.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),noSelectMM.width,noSelectMM.height,-1,1,-1,-1,-1,-1};
	  
	struct objInfo mainMenuStartSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(startSelectMM.width,startSelectMM.height,startSelectMM.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),startSelectMM.width,startSelectMM.height,-1,1,-1,-1,-1,-1};
	  
	struct objInfo mainMenuQuitSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(quitSelectMM.width,quitSelectMM.height,quitSelectMM.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),quitSelectMM.width,quitSelectMM.height,-1,1,-1,-1,-1,-1};
	  
		
	struct objInfo backgroundInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(background.width,background.height,background.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),background.width,background.height,-1,1,-1,-1,-1,-1};
	  	  
	struct objInfo shipInfo = {START_POS_SHIP_x,START_POS_SHIP_y,getPixelArray(ship.width, ship.height, ship.image_pixels),getPixelArray(shipClear.width, 
	    shipClear.height, shipClear.image_pixels),ship.width,ship.height,3,1,-1,-1,-1,-1};
	    
	 struct objInfo shipBulletInfo = {-1,-1,getPixelArray(shipBullet.width,shipBullet.height,shipBullet.image_pixels),getPixelArray(shipBulletClear.width,shipBulletClear.height,
	  shipBulletClear.image_pixels),shipBulletClear.width,shipBulletClear.height,-1,0,-1,-1,-1,-1};
	  
	struct objInfo enemyBulletinfo = {0,0,getPixelArray(enemyBullet.width, enemyBullet.height, enemyBullet.image_pixels),getPixelArray(enemyBulletClear.width, 
	  enemyBulletClear.height, enemyBulletClear.image_pixels),enemyBullet.width,enemyBullet.height,-1,-1,-1,-1,-1,-1}; // This structure only created for storing enemy bullet PIXEL info.
	    
        struct objInfo pawn1info = {PAWN_1_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn2info = {PAWN_2_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	
	struct objInfo pawn3info = {PAWN_3_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn4info = {PAWN_4_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,-1,0,0,0};
	    
	struct objInfo pawn5info = {PAWN_5_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn6info = {PAWN_6_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	   
	struct objInfo pawn7info = {PAWN_7_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn8info = {PAWN_8_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn9info = {PAWN_9_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn10info = {PAWN_10_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	     
	     
	struct objInfo knight1info = {KNIGHT1_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	    
	struct objInfo knight2info = {KNIGHT2_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	
	struct objInfo knight3info = {KNIGHT3_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	
	struct objInfo knight4info = {KNIGHT4_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	
	struct objInfo knight5info = {KNIGHT5_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	    
	    
	struct objInfo queen1info = {QUEEN_START_POS_x,QUEEN1_START_POS_y,getPixelArray(queen.width, queen.height, queen.image_pixels), //we suppose queens are "exposed" to allow them to shoot
	  getPixelArray(queenClear.width, queenClear.height, queenClear.image_pixels),queen.width,queen.height,3,1,1,0,0,0};            //  but if they encounter pawn or knight, the bullet disappears.
	    
	struct objInfo queen2info = {QUEEN_START_POS_x,QUEEN2_START_POS_y,getPixelArray(queen.width, queen.height, queen.image_pixels),
	  getPixelArray(queenClear.width, queenClear.height, queenClear.image_pixels),queen.width,queen.height,3,1,1,0,0,0};    
	  
	struct objInfo brick1info = {BRICK1_START_POS_x,BRICK_START_POS_y,getPixelArray(brick.width, brick.height, brick.image_pixels),
	  getPixelArray(brickClear.width, brickClear.height, brickClear.image_pixels),brick.width,brick.height,3,1,-1,0,0,0}; 
	  
	struct objInfo brick2info = {BRICK2_START_POS_x,BRICK_START_POS_y,getPixelArray(brick.width, brick.height, brick.image_pixels),
	  getPixelArray(brickClear.width, brickClear.height, brickClear.image_pixels),brick.width,brick.height,3,1,-1,0,0,0};    
	  
	struct objInfo brick3info = {BRICK3_START_POS_x,BRICK_START_POS_y,getPixelArray(brick.width, brick.height, brick.image_pixels),
	  getPixelArray(brickClear.width, brickClear.height, brickClear.image_pixels),brick.width,brick.height,3,1,-1,0,0,0}; 
	
	struct replacementBricks rBricks = {getPixelArray(brickMedium.width, brickMedium.height, brickMedium.image_pixels),
	  getPixelArray(brickMediumClear.width, brickMediumClear.height, brickMediumClear.image_pixels),brickMedium.width,brickMedium.height,
	  getPixelArray(brickSmall.width, brickSmall.height, brickSmall.image_pixels),
	  getPixelArray(brickSmallClear.width, brickSmallClear.height, brickSmallClear.image_pixels),brickSmall.width,brickSmall.height};
	  
        struct objInfo heart1info = {HEART1_START_POS_x,HEART_START_POS_y,getPixelArray(heart.width, heart.height, heart.image_pixels),
	  getPixelArray(heartClear.width, heartClear.height, heartClear.image_pixels),heart.width,heart.height,-1,1,-1,0,0,0};
	  
	struct objInfo heart2info = {HEART2_START_POS_x,HEART_START_POS_y,getPixelArray(heart.width, heart.height, heart.image_pixels),
	  getPixelArray(heartClear.width, heartClear.height, heartClear.image_pixels),heart.width,heart.height,-1,1,-1,0,0,0};
	  
	struct objInfo heart3info = {HEART3_START_POS_x,HEART_START_POS_y,getPixelArray(heart.width, heart.height, heart.image_pixels),
	  getPixelArray(heartClear.width, heartClear.height, heartClear.image_pixels),heart.width,heart.height,-1,1,-1,0,0,0};
	  
	struct GameState state; //game state
	state.score = 0;
	state.gameOn = 1;
	
	struct allObj everything;
	
	everything.pawns[0] = pawn1info;
	everything.pawns[1] = pawn2info;
	everything.pawns[2] = pawn3info;
	everything.pawns[3] = pawn4info;
	everything.pawns[4] = pawn5info;
	everything.pawns[5] = pawn6info;
	everything.pawns[6] = pawn7info;
	everything.pawns[7] = pawn8info;
	everything.pawns[8] = pawn9info;
	everything.pawns[9] = pawn10info;
	
	everything.knights[0] = knight1info;
	everything.knights[1] = knight2info;
	everything.knights[2] = knight3info;
	everything.knights[3] = knight4info;
	everything.knights[4] = knight5info;
	
	everything.queens[0] = queen1info;
	everything.queens[1] = queen2info;
	
	everything.bricks[0] = brick1info;
	everything.bricks[1] = brick2info;
	everything.bricks[2] = brick3info;
	
	everything.mainMenu[0] = mainMenuInfo;
	everything.mainMenu[1] = mainMenuStartSelectInfo;
	everything.mainMenu[2] = mainMenuQuitSelectInfo;
	
	everything.hearts[0] = heart1info;
	everything.hearts[1] = heart2info;
	everything.hearts[2] = heart3info;
	
	everything.enemyBullet = enemyBulletinfo;
	
	everything.allObjects[0] = pawn1info;
	everything.allObjects[1] = pawn2info;
	everything.allObjects[2] = pawn3info;
	everything.allObjects[3] = pawn4info;
	everything.allObjects[4] = pawn5info;
	everything.allObjects[5] = pawn6info;
	everything.allObjects[6] = pawn7info;
	everything.allObjects[7] = pawn8info;
	everything.allObjects[8] = pawn9info;
	everything.allObjects[9] = pawn10info;
	everything.allObjects[10] = backgroundInfo;
	everything.allObjects[11] = shipInfo;
	everything.allObjects[12] = shipBulletInfo;
	everything.allObjects[13] = *everything.knights;
	everything.allObjects[14] = *everything.queens;
	everything.allObjects[15] = *everything.hearts;
	//everything.allObjects[16] = enemyBulletInfo;
	everything.smallerBricks = rBricks;
	
	everything.state = state;
    
	//RUN MAIN MENU WITH SNES CONTROLLER
	pthread_t mainMenuThread;
	pthread_attr_t mainMenuThreadAttr;
	pthread_attr_init(&mainMenuThreadAttr);	
	
	pthread_create(&mainMenuThread,&mainMenuThreadAttr,mainMenuRunner,&everything);
	
	pthread_join(mainMenuThread,NULL); //wait for main menu to finish and start a game if thread succeeded
	
	//Print start of game objects
	 	 
	printImage(START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,backgroundInfo.pColorCodes,backgroundInfo.height,backgroundInfo.width,0); //print background	 
      
	printImage(START_POS_SHIP_x,START_POS_SHIP_y,shipInfo.pColorCodes,shipInfo.height,shipInfo.width,1); //print ship
	
	printImage(PAWN_1_START_POS_x,PAWN_START_POS_y,pawn1info.pColorCodes,pawn1info.height,pawn1info.width,0); 
	
	printImage(PAWN_2_START_POS_x,PAWN_START_POS_y,pawn2info.pColorCodes,pawn2info.height,pawn2info.width,0); 
	printImage(PAWN_3_START_POS_x,PAWN_START_POS_y,pawn3info.pColorCodes,pawn3info.height,pawn3info.width,0); 
	printImage(PAWN_4_START_POS_x,PAWN_START_POS_y,pawn4info.pColorCodes,pawn4info.height,pawn4info.width,0);
	printImage(PAWN_5_START_POS_x,PAWN_START_POS_y,pawn5info.pColorCodes,pawn5info.height,pawn5info.width,0); 
	printImage(PAWN_6_START_POS_x,PAWN_START_POS_y,pawn6info.pColorCodes,pawn6info.height,pawn6info.width,0); 
	printImage(PAWN_7_START_POS_x,PAWN_START_POS_y,pawn7info.pColorCodes,pawn7info.height,pawn7info.width,0); 
	printImage(PAWN_8_START_POS_x,PAWN_START_POS_y,pawn8info.pColorCodes,pawn8info.height,pawn8info.width,0); 
	printImage(PAWN_9_START_POS_x,PAWN_START_POS_y,pawn9info.pColorCodes,pawn9info.height,pawn9info.width,0); 
	printImage(PAWN_10_START_POS_x,PAWN_START_POS_y,pawn10info.pColorCodes,pawn10info.height,pawn10info.width,0); 
	
	printImage(KNIGHT1_START_POS_x,KNIGHT_START_POS_y,knight1info.pColorCodes,knight1info.height,knight1info.width,0); 
	printImage(KNIGHT2_START_POS_x,KNIGHT_START_POS_y,knight2info.pColorCodes,knight2info.height,knight2info.width,0); 
	printImage(KNIGHT3_START_POS_x,KNIGHT_START_POS_y,knight3info.pColorCodes,knight3info.height,knight3info.width,0); 
	printImage(KNIGHT4_START_POS_x,KNIGHT_START_POS_y,knight4info.pColorCodes,knight4info.height,knight4info.width,0); 
	printImage(KNIGHT5_START_POS_x,KNIGHT_START_POS_y,knight5info.pColorCodes,knight5info.height,knight5info.width,0);
	
	printImage(QUEEN_START_POS_x,QUEEN1_START_POS_y,queen1info.pColorCodes,queen1info.height,queen1info.width,0);  
	printImage(QUEEN_START_POS_x,QUEEN2_START_POS_y,queen2info.pColorCodes,queen2info.height,queen2info.width,0);  
	
	printImage(BRICK1_START_POS_x,BRICK_START_POS_y,brick1info.pColorCodes,brick1info.height,brick1info.width,0);  
	printImage(BRICK2_START_POS_x,BRICK_START_POS_y,brick2info.pColorCodes,brick2info.height,brick2info.width,0);  
	printImage(BRICK3_START_POS_x,BRICK_START_POS_y,brick3info.pColorCodes,brick3info.height,brick3info.width,0);  
	
	printImage(HEART1_START_POS_x,HEART_START_POS_y,heart1info.pColorCodes,heart1info.height,heart1info.width,0);  
	printImage(HEART2_START_POS_x,HEART_START_POS_y,heart2info.pColorCodes,heart2info.height,heart2info.width,0);  
	printImage(HEART3_START_POS_x,HEART_START_POS_y,heart3info.pColorCodes,heart3info.height,heart3info.width,0);  
	
	
	//Get the threads going
	
	pthread_t monstersMovementThread;
	pthread_attr_t monstersMovementThreadAttr;
	pthread_attr_init(&monstersMovementThreadAttr);
	
	pthread_t playerActionsThread;
	pthread_attr_t playerActionsThreadAttr;
	pthread_attr_init(&playerActionsThreadAttr);
	
	pthread_t playerBulletCollisionsThread;
	pthread_attr_t playerBulletCollisionsThreadAttr;
	pthread_attr_init (&playerBulletCollisionsThreadAttr);
	
	pthread_t updateExposedStatusThread;
	pthread_attr_t updateExposedStatusThreadAttr;
	pthread_attr_init (&updateExposedStatusThreadAttr);
	
	pthread_t updateHeartsThread;
	pthread_attr_t updateHeartsThreadAttr;
	pthread_attr_init (&updateHeartsThreadAttr);
	
	pthread_t enemiesShootThread;
	pthread_attr_t enemiesShootThreadAttr;
	pthread_attr_init (&enemiesShootThreadAttr);
	
	pthread_t enemiesBulletCollisionsThread;
	pthread_attr_t enemiesBulletCollisionsThreadAttr;
	pthread_attr_init (&enemiesBulletCollisionsThreadAttr);
	
	pthread_t winOrLoseThread;
	pthread_attr_t winOrLoseThreadAttr;
	pthread_attr_init (&winOrLoseThreadAttr);
	
	pthread_t scoreDisplayThread;
	pthread_attr_t scoreDisplayThreadAttr;
	pthread_attr_init (&scoreDisplayThreadAttr);
      
	pthread_create(&updateHeartsThread,&updateHeartsThreadAttr,updateHeartsRunner,&everything); //Drawing hearts on screen according to current player's lives
	pthread_create(&monstersMovementThread,&monstersMovementThreadAttr,monstersMovementRunner,&everything); //Movement of monsters - continuous
	pthread_create(&playerBulletCollisionsThread,&playerBulletCollisionsThreadAttr,playerBulletCollisionsRunner,&everything); //Checking collitions of player's bullet
	pthread_create(&playerActionsThread,&playerActionsThreadAttr,playerActionsRunner,&everything); //Checking player's keywords in game
	pthread_create(&updateExposedStatusThread,&updateExposedStatusThreadAttr,updateExposedStatusRunner,&everything);
	pthread_create(&enemiesShootThread,&enemiesShootThreadAttr,enemiesShootRunner,&everything);
	pthread_create(&enemiesBulletCollisionsThread,&enemiesBulletCollisionsThreadAttr,enemiesBulletCollisionsRunner,&everything);
	pthread_create(&winOrLoseThread,&winOrLoseThreadAttr,winOrLoseRunner,&everything);
	pthread_create(&scoreDisplayThread,&scoreDisplayThreadAttr,scoreDisplayRunner,&everything);
	
	
	pthread_join(updateHeartsThread,NULL);
	pthread_join(monstersMovementThread,NULL);
	pthread_join(playerActionsThread,NULL);
	pthread_join(playerBulletCollisionsThread,NULL);
	pthread_join(updateExposedStatusThread,NULL);
	pthread_join(enemiesShootThread,NULL);
	pthread_join(enemiesBulletCollisionsThread,NULL);
	pthread_join(winOrLoseThread,NULL);
	pthread_join(scoreDisplayThread,NULL);
	
	

return 0;
}

/**
 * This thread is reponsible for restarting the game
 */
void *restartGameRunner(){
  //Initialize SNES
    
	gpio = gpioPtr();	//Base address
	
	Init_GPIO(LAT,001); //Set GPIO pin 9 (LATCH) to output
	Init_GPIO(DAT,000); //Set GPIO pin 10 (DATA) to input
	Init_GPIO(CLK,001); //Set GPIO pin 11 (CLOCK) to output
	
	frameBufferStruct = initFbInfo(); //Initialize info about screen
	
	 
	/**
	 * Initialize structures of objects - Background, Ship, Pawns (10), Knights(5),Queens(2) , Obstacles(3).
	 */ 
	 
	struct objInfo mainMenuInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(noSelectMM.width,noSelectMM.height,noSelectMM.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),noSelectMM.width,noSelectMM.height,-1,1,-1,-1,-1,-1};
	  
	struct objInfo mainMenuStartSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(startSelectMM.width,startSelectMM.height,startSelectMM.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),startSelectMM.width,startSelectMM.height,-1,1,-1,-1,-1,-1};
	  
	struct objInfo mainMenuQuitSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(quitSelectMM.width,quitSelectMM.height,quitSelectMM.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),quitSelectMM.width,quitSelectMM.height,-1,1,-1,-1,-1,-1};
	  
		
	struct objInfo backgroundInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(background.width,background.height,background.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),background.width,background.height,-1,1,-1,-1,-1,-1};
	  	  
	struct objInfo shipInfo = {START_POS_SHIP_x,START_POS_SHIP_y,getPixelArray(ship.width, ship.height, ship.image_pixels),getPixelArray(shipClear.width, 
	    shipClear.height, shipClear.image_pixels),ship.width,ship.height,3,1,-1,-1,-1,-1};
	    
	 struct objInfo shipBulletInfo = {-1,-1,getPixelArray(shipBullet.width,shipBullet.height,shipBullet.image_pixels),getPixelArray(shipBulletClear.width,shipBulletClear.height,
	  shipBulletClear.image_pixels),shipBulletClear.width,shipBulletClear.height,-1,0,-1,-1,-1,-1};
	  
	struct objInfo enemyBulletinfo = {0,0,getPixelArray(enemyBullet.width, enemyBullet.height, enemyBullet.image_pixels),getPixelArray(enemyBulletClear.width, 
	  enemyBulletClear.height, enemyBulletClear.image_pixels),enemyBullet.width,enemyBullet.height,-1,-1,-1,-1,-1,-1}; // This structure only created for storing enemy bullet PIXEL info.
	    
        struct objInfo pawn1info = {PAWN_1_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn2info = {PAWN_2_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	
	struct objInfo pawn3info = {PAWN_3_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn4info = {PAWN_4_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,-1,0,0,0};
	    
	struct objInfo pawn5info = {PAWN_5_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn6info = {PAWN_6_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	   
	struct objInfo pawn7info = {PAWN_7_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn8info = {PAWN_8_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn9info = {PAWN_9_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	    
	struct objInfo pawn10info = {PAWN_10_START_POS_x,PAWN_START_POS_y,getPixelArray(pawn.width, pawn.height, pawn.image_pixels),getPixelArray(pawnClear.width, 
	    pawnClear.height, pawnClear.image_pixels),pawn.width,pawn.height,1,1,1,0,0,0};
	     
	     
	struct objInfo knight1info = {KNIGHT1_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	    
	struct objInfo knight2info = {KNIGHT2_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	
	struct objInfo knight3info = {KNIGHT3_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	
	struct objInfo knight4info = {KNIGHT4_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	
	struct objInfo knight5info = {KNIGHT5_START_POS_x,KNIGHT_START_POS_y,getPixelArray(knight.width, knight.height, knight.image_pixels),getPixelArray(knightClear.width, 
	    knightClear.height, knightClear.image_pixels),knight.width,knight.height,2,1,0,0,0,0};
	    
	    
	struct objInfo queen1info = {QUEEN_START_POS_x,QUEEN1_START_POS_y,getPixelArray(queen.width, queen.height, queen.image_pixels), //we suppose queens are "exposed" to allow them to shoot
	  getPixelArray(queenClear.width, queenClear.height, queenClear.image_pixels),queen.width,queen.height,3,1,1,0,0,0};            //  but if they encounter pawn or knight, the bullet disappears.
	    
	struct objInfo queen2info = {QUEEN_START_POS_x,QUEEN2_START_POS_y,getPixelArray(queen.width, queen.height, queen.image_pixels),
	  getPixelArray(queenClear.width, queenClear.height, queenClear.image_pixels),queen.width,queen.height,3,1,1,0,0,0};    
	  
	struct objInfo brick1info = {BRICK1_START_POS_x,BRICK_START_POS_y,getPixelArray(brick.width, brick.height, brick.image_pixels),
	  getPixelArray(brickClear.width, brickClear.height, brickClear.image_pixels),brick.width,brick.height,3,1,-1,0,0,0}; 
	  
	struct objInfo brick2info = {BRICK2_START_POS_x,BRICK_START_POS_y,getPixelArray(brick.width, brick.height, brick.image_pixels),
	  getPixelArray(brickClear.width, brickClear.height, brickClear.image_pixels),brick.width,brick.height,3,1,-1,0,0,0};    
	  
	struct objInfo brick3info = {BRICK3_START_POS_x,BRICK_START_POS_y,getPixelArray(brick.width, brick.height, brick.image_pixels),
	  getPixelArray(brickClear.width, brickClear.height, brickClear.image_pixels),brick.width,brick.height,3,1,-1,0,0,0}; 
	
	struct replacementBricks rBricks = {getPixelArray(brickMedium.width, brickMedium.height, brickMedium.image_pixels),
	  getPixelArray(brickMediumClear.width, brickMediumClear.height, brickMediumClear.image_pixels),brickMedium.width,brickMedium.height,
	  getPixelArray(brickSmall.width, brickSmall.height, brickSmall.image_pixels),
	  getPixelArray(brickSmallClear.width, brickSmallClear.height, brickSmallClear.image_pixels),brickSmall.width,brickSmall.height};
	  
        struct objInfo heart1info = {HEART1_START_POS_x,HEART_START_POS_y,getPixelArray(heart.width, heart.height, heart.image_pixels),
	  getPixelArray(heartClear.width, heartClear.height, heartClear.image_pixels),heart.width,heart.height,-1,1,-1,0,0,0};
	  
	struct objInfo heart2info = {HEART2_START_POS_x,HEART_START_POS_y,getPixelArray(heart.width, heart.height, heart.image_pixels),
	  getPixelArray(heartClear.width, heartClear.height, heartClear.image_pixels),heart.width,heart.height,-1,1,-1,0,0,0};
	  
	struct objInfo heart3info = {HEART3_START_POS_x,HEART_START_POS_y,getPixelArray(heart.width, heart.height, heart.image_pixels),
	  getPixelArray(heartClear.width, heartClear.height, heartClear.image_pixels),heart.width,heart.height,-1,1,-1,0,0,0};
	  
	struct GameState state; //game state
	state.score = 0;
	state.gameOn = 1;
	
	struct allObj everything;
	
	everything.pawns[0] = pawn1info;
	everything.pawns[1] = pawn2info;
	everything.pawns[2] = pawn3info;
	everything.pawns[3] = pawn4info;
	everything.pawns[4] = pawn5info;
	everything.pawns[5] = pawn6info;
	everything.pawns[6] = pawn7info;
	everything.pawns[7] = pawn8info;
	everything.pawns[8] = pawn9info;
	everything.pawns[9] = pawn10info;
	
	everything.knights[0] = knight1info;
	everything.knights[1] = knight2info;
	everything.knights[2] = knight3info;
	everything.knights[3] = knight4info;
	everything.knights[4] = knight5info;
	
	everything.queens[0] = queen1info;
	everything.queens[1] = queen2info;
	
	everything.bricks[0] = brick1info;
	everything.bricks[1] = brick2info;
	everything.bricks[2] = brick3info;
	
	everything.mainMenu[0] = mainMenuInfo;
	everything.mainMenu[1] = mainMenuStartSelectInfo;
	everything.mainMenu[2] = mainMenuQuitSelectInfo;
	
	everything.hearts[0] = heart1info;
	everything.hearts[1] = heart2info;
	everything.hearts[2] = heart3info;
	
	everything.enemyBullet = enemyBulletinfo;
	
	everything.allObjects[0] = pawn1info;
	everything.allObjects[1] = pawn2info;
	everything.allObjects[2] = pawn3info;
	everything.allObjects[3] = pawn4info;
	everything.allObjects[4] = pawn5info;
	everything.allObjects[5] = pawn6info;
	everything.allObjects[6] = pawn7info;
	everything.allObjects[7] = pawn8info;
	everything.allObjects[8] = pawn9info;
	everything.allObjects[9] = pawn10info;
	everything.allObjects[10] = backgroundInfo;
	everything.allObjects[11] = shipInfo;
	everything.allObjects[12] = shipBulletInfo;
	everything.allObjects[13] = *everything.knights;
	everything.allObjects[14] = *everything.queens;
	everything.allObjects[15] = *everything.hearts;
	//everything.allObjects[16] = enemyBulletInfo;
	everything.smallerBricks = rBricks;
	
	everything.state = state;
	
	//Print start of game objects
	 	 
	printImage(START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,backgroundInfo.pColorCodes,backgroundInfo.height,backgroundInfo.width,0); //print background	 
      
	printImage(START_POS_SHIP_x,START_POS_SHIP_y,shipInfo.pColorCodes,shipInfo.height,shipInfo.width,1); //print ship
	
	printImage(PAWN_1_START_POS_x,PAWN_START_POS_y,pawn1info.pColorCodes,pawn1info.height,pawn1info.width,0); 
	
	printImage(PAWN_2_START_POS_x,PAWN_START_POS_y,pawn2info.pColorCodes,pawn2info.height,pawn2info.width,0); 
	printImage(PAWN_3_START_POS_x,PAWN_START_POS_y,pawn3info.pColorCodes,pawn3info.height,pawn3info.width,0); 
	printImage(PAWN_4_START_POS_x,PAWN_START_POS_y,pawn4info.pColorCodes,pawn4info.height,pawn4info.width,0);
	printImage(PAWN_5_START_POS_x,PAWN_START_POS_y,pawn5info.pColorCodes,pawn5info.height,pawn5info.width,0); 
	printImage(PAWN_6_START_POS_x,PAWN_START_POS_y,pawn6info.pColorCodes,pawn6info.height,pawn6info.width,0); 
	printImage(PAWN_7_START_POS_x,PAWN_START_POS_y,pawn7info.pColorCodes,pawn7info.height,pawn7info.width,0); 
	printImage(PAWN_8_START_POS_x,PAWN_START_POS_y,pawn8info.pColorCodes,pawn8info.height,pawn8info.width,0); 
	printImage(PAWN_9_START_POS_x,PAWN_START_POS_y,pawn9info.pColorCodes,pawn9info.height,pawn9info.width,0); 
	printImage(PAWN_10_START_POS_x,PAWN_START_POS_y,pawn10info.pColorCodes,pawn10info.height,pawn10info.width,0); 
	
	printImage(KNIGHT1_START_POS_x,KNIGHT_START_POS_y,knight1info.pColorCodes,knight1info.height,knight1info.width,0); 
	printImage(KNIGHT2_START_POS_x,KNIGHT_START_POS_y,knight2info.pColorCodes,knight2info.height,knight2info.width,0); 
	printImage(KNIGHT3_START_POS_x,KNIGHT_START_POS_y,knight3info.pColorCodes,knight3info.height,knight3info.width,0); 
	printImage(KNIGHT4_START_POS_x,KNIGHT_START_POS_y,knight4info.pColorCodes,knight4info.height,knight4info.width,0); 
	printImage(KNIGHT5_START_POS_x,KNIGHT_START_POS_y,knight5info.pColorCodes,knight5info.height,knight5info.width,0);
	
	printImage(QUEEN_START_POS_x,QUEEN1_START_POS_y,queen1info.pColorCodes,queen1info.height,queen1info.width,0);  
	printImage(QUEEN_START_POS_x,QUEEN2_START_POS_y,queen2info.pColorCodes,queen2info.height,queen2info.width,0);  
	
	printImage(BRICK1_START_POS_x,BRICK_START_POS_y,brick1info.pColorCodes,brick1info.height,brick1info.width,0);  
	printImage(BRICK2_START_POS_x,BRICK_START_POS_y,brick2info.pColorCodes,brick2info.height,brick2info.width,0);  
	printImage(BRICK3_START_POS_x,BRICK_START_POS_y,brick3info.pColorCodes,brick3info.height,brick3info.width,0);  
	
	printImage(HEART1_START_POS_x,HEART_START_POS_y,heart1info.pColorCodes,heart1info.height,heart1info.width,0);  
	printImage(HEART2_START_POS_x,HEART_START_POS_y,heart2info.pColorCodes,heart2info.height,heart2info.width,0);  
	printImage(HEART3_START_POS_x,HEART_START_POS_y,heart3info.pColorCodes,heart3info.height,heart3info.width,0);  
	
	
	//Get the threads going
	
	pthread_t monstersMovementThread;
	pthread_attr_t monstersMovementThreadAttr;
	pthread_attr_init(&monstersMovementThreadAttr);
	
	pthread_t playerActionsThread;
	pthread_attr_t playerActionsThreadAttr;
	pthread_attr_init(&playerActionsThreadAttr);
	
	pthread_t playerBulletCollisionsThread;
	pthread_attr_t playerBulletCollisionsThreadAttr;
	pthread_attr_init (&playerBulletCollisionsThreadAttr);
	
	pthread_t updateExposedStatusThread;
	pthread_attr_t updateExposedStatusThreadAttr;
	pthread_attr_init (&updateExposedStatusThreadAttr);
	
	pthread_t updateHeartsThread;
	pthread_attr_t updateHeartsThreadAttr;
	pthread_attr_init (&updateHeartsThreadAttr);
	
	pthread_t enemiesShootThread;
	pthread_attr_t enemiesShootThreadAttr;
	pthread_attr_init (&enemiesShootThreadAttr);
	
	pthread_t enemiesBulletCollisionsThread;
	pthread_attr_t enemiesBulletCollisionsThreadAttr;
	pthread_attr_init (&enemiesBulletCollisionsThreadAttr);
	
	pthread_t winOrLoseThread;
	pthread_attr_t winOrLoseThreadAttr;
	pthread_attr_init (&winOrLoseThreadAttr);
	
	pthread_t scoreDisplayThread;
	pthread_attr_t scoreDisplayThreadAttr;
	pthread_attr_init (&scoreDisplayThreadAttr);
      
	pthread_create(&updateHeartsThread,&updateHeartsThreadAttr,updateHeartsRunner,&everything); //Drawing hearts on screen according to current player's lives
	pthread_create(&monstersMovementThread,&monstersMovementThreadAttr,monstersMovementRunner,&everything); //Movement of monsters - continuous
	pthread_create(&playerBulletCollisionsThread,&playerBulletCollisionsThreadAttr,playerBulletCollisionsRunner,&everything); //Checking collitions of player's bullet
	pthread_create(&playerActionsThread,&playerActionsThreadAttr,playerActionsRunner,&everything); //Checking player's keywords in game
	pthread_create(&updateExposedStatusThread,&updateExposedStatusThreadAttr,updateExposedStatusRunner,&everything);
	pthread_create(&enemiesShootThread,&enemiesShootThreadAttr,enemiesShootRunner,&everything);
	pthread_create(&enemiesBulletCollisionsThread,&enemiesBulletCollisionsThreadAttr,enemiesBulletCollisionsRunner,&everything);
	pthread_create(&winOrLoseThread,&winOrLoseThreadAttr,winOrLoseRunner,&everything);
	pthread_create(&scoreDisplayThread,&scoreDisplayThreadAttr,scoreDisplayRunner,&everything);
	
	
	pthread_join(updateHeartsThread,NULL);
	pthread_join(monstersMovementThread,NULL);
	pthread_join(playerActionsThread,NULL);
	pthread_join(playerBulletCollisionsThread,NULL);
	pthread_join(updateExposedStatusThread,NULL);
	pthread_join(enemiesShootThread,NULL);
	pthread_join(enemiesBulletCollisionsThread,NULL);
	pthread_join(winOrLoseThread,NULL);
	pthread_join(scoreDisplayThread,NULL);

  
  pthread_exit(0);
  
}

/**
 * This thread is responsible for actions of main menu. 
 */
void *mainMenuRunner(void *param){
    //MENU THREAD HERE & wait for key, either exit: quit main & blackscreen, or play, continue
	
    struct allObj *objects;
    objects = param;
    
    int *pButtonCode;              //Button code as as pointer to array of integers
    char *pButtonName = "None";	   //Button name as string
    int currentSelection = 0;      //0 for nothing, 1 for start, 2 for quit
    printImage(START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,objects->mainMenu[0].pColorCodes,objects->mainMenu[0].height,objects->mainMenu[0].width,0); //print MAIN MENU
	
     while(objects->state.gameOn){

      delayMicroseconds(110000); //Delay for smoother transition with pressing and releasing buttons - more natural
		
      pButtonCode = Read_SNES();
		
	//Check if button has been released
      if (strcmp(getButtonName(pButtonCode),pButtonName) == 0 ){ continue;} 
		
      pButtonName = getButtonName(pButtonCode); 
      
      //Detect button pressed 
      if (strcmp(getButtonName(pButtonCode),"") != 0){ 
		  
	  if(strcmp(getButtonName(pButtonCode),"A") == 0) {
	    if (currentSelection == 1){
	      break; //start game here
	    }else if(currentSelection == 2){
	      printImage(START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,objects->allObjects[10].pColorCodes,objects->allObjects[10].height,objects->allObjects[10].width,0);
	      exit(0);}
	    }  
	   
	   else if(strcmp(getButtonName(pButtonCode),"Joy-Pad DOWN") == 0) {
	    //printf("Entering If statement for Joy Pad Down button \n");
	    currentSelection = 2;
	    printImage(START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,objects->mainMenu[2].pColorCodes,objects->mainMenu[2].height,objects->mainMenu[2].width,0);
	  }
	  
	   
	  else if(strcmp(getButtonName(pButtonCode),"Joy-pad UP") == 0) {
	    currentSelection = 1;
	    printImage(START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,objects->mainMenu[1].pColorCodes,objects->mainMenu[1].height,objects->mainMenu[1].width,0); //print Menu with START selection
	  }
	  
	  
	  
	  //continue;
	}
  }
  pthread_exit(0);
}

  /**
   * This thread checks whether the player lost or won
   */
void *winOrLoseRunner(void *param){
    struct allObj *objects;
    objects = param;
    
    int numberOfAliveMonsters = 0;
    
  while(1){
    //Check current number of monsters alive
    for(int i=0;i<10;i++){if(objects->pawns[i].active){numberOfAliveMonsters +=1;}}
    for(int j=0;j<5;j++){if(objects->knights[j].active){numberOfAliveMonsters +=1;}}
    for(int k=0;k<2;k++){if(objects->queens[k].active){numberOfAliveMonsters +=1;}}
    
    if (!objects->allObjects[11].active && objects->allObjects[11].health == 0 && !objects->state.gameOn){ //check if player lost and is dead
     
        //display lose menu options
	pthread_t loseMenuThread;
	pthread_attr_t loseMenuThreadAttr;
	pthread_attr_init (&loseMenuThreadAttr);
	
	pthread_create(&loseMenuThread,&loseMenuThreadAttr,loseMenuRunner,&objects);
	
	pthread_join(loseMenuThread,NULL);

	pthread_exit(0);
	
    } else if (numberOfAliveMonsters == 0 && objects->allObjects[11].health > 0 && objects->allObjects[11].active){ //check if player killed all the monsters and is alive
	objects->state.gameOn = 0; //Stop the game
	
	//display win menu options
	pthread_t winMenuThread;
	pthread_attr_t winMenuThreadAttr;
	pthread_attr_init (&winMenuThreadAttr);
	
	pthread_create(&winMenuThread,&winMenuThreadAttr,winMenuRunner,&objects);
	
	pthread_join(winMenuThread,NULL);
	
	pthread_exit(0);
	
      
      }
    numberOfAliveMonsters = 0; //reset counter
    }
  
  pthread_exit(0);
  }
  
  /**
   * This thread is for main menu when user WINS
   */
void *winMenuRunner(void *param){
    
    struct allObj *objects;
    objects = param;
    
    int *pButtonCode;              //Button code as as pointer to array of integers
    char *pButtonName = "None";	   //Button name as string
    int currentSelection = 0;      //0 for nothing, 1 for restart, 2 for quit
      
      struct objInfo backgroundInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(background.width,background.height,background.image_pixels),
	getPixelArray(background.width,background.height,background.image_pixels),background.width,background.height,-1,1,-1,-1,-1,-1};
      
      struct objInfo winNoSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(winNoSelect.width,winNoSelect.height,winNoSelect.image_pixels),
	getPixelArray(background.width,background.height,background.image_pixels),winNoSelect.width,winNoSelect.height,-1,1,-1,-1,-1,-1};
	
      struct objInfo winRestartSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(winRestartSelect.width,winRestartSelect.height,winRestartSelect.image_pixels),
	getPixelArray(background.width,background.height,background.image_pixels),winRestartSelect.width,winRestartSelect.height,-1,1,-1,-1,-1,-1};
	
      struct objInfo winQuitSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(winQuitSelect.width,winQuitSelect.height,winQuitSelect.image_pixels),
	getPixelArray(background.width,background.height,background.image_pixels),winQuitSelect.width,winQuitSelect.height,-1,1,-1,-1,-1,-1};
	
      printImage(winNoSelectInfo.currentX,winNoSelectInfo.currentY,winNoSelectInfo.pColorCodes,winNoSelectInfo.height,winNoSelectInfo.width,0); 
	
     while(1){
    
      delayMicroseconds(110000); //Delay for smoother transition with pressing and releasing buttons - more natural
		
      pButtonCode = Read_SNES();
		
	//Check if button has been released
      if (strcmp(getButtonName(pButtonCode),pButtonName) == 0 ){ continue;} 
		
      pButtonName = getButtonName(pButtonCode); 
      
      //Detect button pressed 
      if (strcmp(getButtonName(pButtonCode),"") != 0){ 
	  
	  if(strcmp(getButtonName(pButtonCode),"A") == 0) {
	    if (currentSelection == 1){ //restart is selected
	      
	      pthread_t restartGameThread;
	      pthread_attr_t restartGameThreadAttr;
	      pthread_attr_init (&restartGameThreadAttr);
	      pthread_create(&restartGameThread,&restartGameThreadAttr,restartGameRunner,&objects);
	      
	      pthread_join(restartGameThread,NULL);
	      
	      pthread_exit(0);
	      
	    }else if(currentSelection == 2){
	       printImage(backgroundInfo.currentX,backgroundInfo.currentY,backgroundInfo.pColorCodes,backgroundInfo.height,backgroundInfo.width,0); 
	      exit(0);}
	    }  
	   
	   else if(strcmp(getButtonName(pButtonCode),"Joy-Pad DOWN") == 0) {
	    currentSelection = 2;
	    printImage(winQuitSelectInfo.currentX,winQuitSelectInfo.currentY,winQuitSelectInfo.pColorCodes,winQuitSelectInfo.height,winQuitSelectInfo.width,0);
	  }
	   
	  else if(strcmp(getButtonName(pButtonCode),"Joy-pad UP") == 0) {
	    currentSelection = 1;
	    printImage(winRestartSelectInfo.currentX,winRestartSelectInfo.currentY,winRestartSelectInfo.pColorCodes,winRestartSelectInfo.height,winRestartSelectInfo.width,0);
	  }
	  
	}
  }
	
  pthread_exit(0);}
  
  
/**
 * This thread is for main menu when user LOSES
 */
void *loseMenuRunner(void *param){
  //LOSE MENU THREAD HERE & wait for key
	
    struct allObj *objects;
    objects = param;
    
    int *pButtonCode;              //Button code as as pointer to array of integers
    char *pButtonName = "None";	   //Button name as string
    int currentSelection = 0;      //0 for nothing, 1 for restart, 2 for quit
    
    struct objInfo backgroundInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(background.width,background.height,background.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),background.width,background.height,-1,1,-1,-1,-1,-1};
    
     struct objInfo loseNoSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(loseNoSelect.width,loseNoSelect.height,loseNoSelect.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),loseNoSelect.width,loseNoSelect.height,-1,1,-1,-1,-1,-1};
	  
     struct objInfo loseRestartSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(loseRestartSelect.width,loseRestartSelect.height,loseRestartSelect.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),loseRestartSelect.width,loseRestartSelect.height,-1,1,-1,-1,-1,-1};
	  
    struct objInfo loseQuitSelectInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(loseQuitSelect.width,loseQuitSelect.height,loseQuitSelect.image_pixels),
	  getPixelArray(background.width,background.height,background.image_pixels),loseQuitSelect.width,loseQuitSelect.height,-1,1,-1,-1,-1,-1};
	  
     printImage(loseNoSelectInfo.currentX,loseNoSelectInfo.currentY,loseNoSelectInfo.pColorCodes,loseNoSelectInfo.height,loseNoSelectInfo.width,0); 
	
     while(1){
    
      delayMicroseconds(110000); //Delay for smoother transition with pressing and releasing buttons - more natural
		
      pButtonCode = Read_SNES();
		
	//Check if button has been released
      if (strcmp(getButtonName(pButtonCode),pButtonName) == 0 ){ continue;} 
		
      pButtonName = getButtonName(pButtonCode); 
      
      //Detect button pressed 
      if (strcmp(getButtonName(pButtonCode),"") != 0){ 
	  
	  if(strcmp(getButtonName(pButtonCode),"A") == 0) {

	    if (currentSelection == 1){ //restart is selected
	      pthread_t restartGameThread;
	      pthread_attr_t restartGameThreadAttr;
	      pthread_attr_init (&restartGameThreadAttr);
	      pthread_create(&restartGameThread,&restartGameThreadAttr,restartGameRunner,&objects);
	      
	      pthread_join(restartGameThread,NULL);
	      
	      pthread_exit(0);
	      
	    }else if(currentSelection == 2){
	       printImage(backgroundInfo.currentX,backgroundInfo.currentY,backgroundInfo.pColorCodes,backgroundInfo.height,backgroundInfo.width,0); 
	      exit(0);}
	    }  
	   
	   else if(strcmp(getButtonName(pButtonCode),"Joy-Pad DOWN") == 0) {
	    currentSelection = 2;
	    printImage(loseQuitSelectInfo.currentX,loseQuitSelectInfo.currentY,loseQuitSelectInfo.pColorCodes,loseQuitSelectInfo.height,loseQuitSelectInfo.width,0);
	  }
	  
	   
	  else if(strcmp(getButtonName(pButtonCode),"Joy-pad UP") == 0) {
	    currentSelection = 1;
	    printImage(loseRestartSelectInfo.currentX,loseRestartSelectInfo.currentY,loseRestartSelectInfo.pColorCodes,loseRestartSelectInfo.height,loseRestartSelectInfo.width,0);
	  }
	  
	}
  }
  pthread_exit(0);}
  
  
/**
 * This thread is for when a player shoots a bullet
 */
void *bulletRunner(void *param){
  struct allObj *objects;
  objects = param;
  playerShoot(&objects->allObjects[11],&objects->allObjects[12]);
  pthread_exit(0);
}

/**
 * This thread is for enemy shooting
 */
void *enemiesShootRunner(void *param){
  struct allObj *objects;
  objects = param;
  
  pthread_t pawnsShootThread;
  pthread_attr_t pawnsShootThreadAttr;
  pthread_attr_init (&pawnsShootThreadAttr);
  
   pthread_t knightsShootThread;
  pthread_attr_t knightsShootThreadAttr;
  pthread_attr_init (&knightsShootThreadAttr);
  
  pthread_t queensShootThread;
  pthread_attr_t queensShootThreadAttr;
  pthread_attr_init (&queensShootThreadAttr);
  
  pthread_create(&knightsShootThread,&knightsShootThreadAttr,knightShootRunner,objects);
  pthread_create(&pawnsShootThread,&pawnsShootThreadAttr,pawnShootRunner,objects);
  pthread_create(&queensShootThread,&queensShootThreadAttr,queenShootRunner,objects);
  
  pthread_join(pawnsShootThread,NULL);
  pthread_join(knightsShootThread,NULL);
  pthread_join(queensShootThread,NULL);
  pthread_exit(0);
  
  
  }

/**
 * This thread is for queens shooting
 */
void *queenShootRunner(void *param){
  
  struct allObj *objects;
  objects = param;
  long int i; //queen number that will shoot. Index 
  
  while(objects->state.gameOn){
    
    i = random_at_most(1); //Generate random num, of queen that will shoot
    
    enemyShoot(&objects->queens[i],&objects->enemyBullet,&objects->state);
  }
  pthread_exit(0);
}

/**
 * Thread responsible for knight's shooting action
 */
void *knightShootRunner(void *param){
  
  struct allObj *objects;
  objects = param;
  long int i; //knight number that will shoot. Index 
  
  while(objects->state.gameOn){
    
    i = random_at_most(4); //Generate random num, of knight that will shoot
    
    enemyShoot(&objects->knights[i],&objects->enemyBullet,&objects->state);
  }

  
  pthread_exit(0);
  
}

/**
 * Thread responsible for pawn's shooting action
 */
void *pawnShootRunner(void *param){
  
  struct allObj *objects;
  objects = param;
  long int i; //pawn number that will shoot. Index 
  
  while(objects->state.gameOn){
    
    i = random_at_most(9); //Generate random num, of pawn that will shoot
    
    enemyShoot(&objects->pawns[i],&objects->enemyBullet,&objects->state);
    
    delay(bulletFrequencyDelay);
  }
    pthread_exit(0);
}

/**
 * Function responsible for enemy's shooting action
 */
void enemyShoot(struct objInfo *shooter,struct objInfo *bulletInfo,struct GameState *game){
  
  if(shooter->active && shooter->health >0 && shooter->exposed){ //if monster is alive & exposed
      
      if(shooter->bulletActive == 0){
	shooter->bulletActive = 1;
	
	int bulletXStart = (shooter->width/2) - (bulletInfo->width/2) + (shooter->currentX);
	int bulletYStart = (shooter->currentY) + (shooter->height) + (bulletInfo->height/2) ;
      
	shooter->bulletXCoordinate = bulletXStart;
	shooter->bulletYCoordinate = bulletYStart;
      
	printImage(bulletXStart,bulletYStart,bulletInfo->pColorCodes,bulletInfo->height,bulletInfo->width,0);
	
	int quit=0;
	while(!quit && shooter->bulletActive && game->gameOn){
	  
	    delay(monstersBulletDelay);
	    
	    printImage(shooter->bulletXCoordinate,shooter->bulletYCoordinate,
	       bulletInfo->pClearColorCodes,bulletInfo->height,bulletInfo->width,1); //black out the image
	       
	    quit = printImage(shooter->bulletXCoordinate ,shooter->bulletYCoordinate + bulletMoveSpeed,
	       bulletInfo->pColorCodes,bulletInfo->height,bulletInfo->width,1); //move it down
	       
  
	    if(quit){ //check if image was printed out of bounds
	      printImage(shooter->bulletXCoordinate,shooter->bulletYCoordinate + bulletMoveSpeed,
	         bulletInfo->pClearColorCodes,bulletInfo->height,bulletInfo->width,1); //black out the image
		 
	      printImage(shooter->bulletXCoordinate,shooter->bulletYCoordinate,
	          bulletInfo->pClearColorCodes,bulletInfo->height,bulletInfo->width,1);
	      break;
	    }
	    shooter->bulletYCoordinate  += bulletMoveSpeed; 
	    
	  }
	//quit is 1
	shooter->bulletActive = 0;
	printImage(shooter->bulletXCoordinate,shooter->bulletYCoordinate + bulletMoveSpeed,
	         bulletInfo->pClearColorCodes,bulletInfo->height,bulletInfo->width,1); //black out the image
	
			
      }     
  }
}

/**
 * This thread updates hearts visible in the game depending on player's lives
 */
void *updateHeartsRunner(void *param){
  struct allObj *objects;
  objects = param;
  
  while(objects->state.gameOn){
      
    if(objects->allObjects[11].health == 2){
      
      printImage(HEART1_START_POS_x,HEART_START_POS_y,objects->hearts[0].pClearColorCodes,objects->hearts[0].height,objects->hearts[0].width,0);  //delete heart 1
      printImage(HEART2_START_POS_x,HEART_START_POS_y,objects->hearts[1].pColorCodes,objects->hearts[1].height,objects->hearts[1].width,0); //re-print heart 2 in case player shot it
      printImage(HEART3_START_POS_x,HEART_START_POS_y,objects->hearts[2].pColorCodes,objects->hearts[2].height,objects->hearts[2].width,0); //re-print heart 3 in case player shot it
      \
      
    }
    else if(objects->allObjects[11].health == 1){
      printImage(HEART1_START_POS_x,HEART_START_POS_y,objects->hearts[0].pClearColorCodes,objects->hearts[0].height,objects->hearts[0].width,0); //delete heart 1
      printImage(HEART2_START_POS_x,HEART_START_POS_y,objects->hearts[0].pClearColorCodes,objects->hearts[0].height,objects->hearts[0].width,0); //delete heart 2
      printImage(HEART3_START_POS_x,HEART_START_POS_y,objects->hearts[2].pColorCodes,objects->hearts[2].height,objects->hearts[2].width,0); //re-print heart 3 in case player shot it

    }
    else if(objects->allObjects[11].health == 0){ 
      printImage(HEART1_START_POS_x,HEART_START_POS_y,objects->hearts[0].pClearColorCodes,objects->hearts[0].height,objects->hearts[0].width,0); 
      printImage(HEART2_START_POS_x,HEART_START_POS_y,objects->hearts[0].pClearColorCodes,objects->hearts[0].height,objects->hearts[0].width,0); 
      printImage(HEART3_START_POS_x,HEART_START_POS_y,objects->hearts[0].pClearColorCodes,objects->hearts[0].height,objects->hearts[0].width,0); 
      objects->allObjects[11].active = 0;
      objects->allObjects[11].health = 0;
      objects->state.gameOn = 0;
      break;
    }
    else{
      printImage(HEART1_START_POS_x,HEART_START_POS_y,objects->hearts[0].pColorCodes,objects->hearts[0].height,objects->hearts[0].width,0);  //re-print heart 1 in case player shot it
      printImage(HEART2_START_POS_x,HEART_START_POS_y,objects->hearts[1].pColorCodes,objects->hearts[1].height,objects->hearts[1].width,0); //re-print heart 2 in case player shot it
      printImage(HEART3_START_POS_x,HEART_START_POS_y,objects->hearts[2].pColorCodes,objects->hearts[2].height,objects->hearts[2].width,0); //re-print heart 3 in case player shot it
    }
  }
    
  pthread_exit(0);
  }

/**
 * This thread checks for buttons pressed on SNES controller and responds accordingly.
 */
void *playerActionsRunner(void *param){

  struct allObj *objects;
  objects = param;
  
  pthread_t playerBulletThread;
  pthread_attr_t playerBulletThreadAttr;
  pthread_attr_init(&playerBulletThreadAttr);

  int *pButtonCode;              //Button code as as pointer to array of integers
  char *pButtonName = "None";	   //Button name as string
	
  while(objects->state.gameOn){

      delayMicroseconds(10000); //Delay for smoother transition with pressing and releasing buttons - more natural
		
      pButtonCode = Read_SNES();
		
	//Check if button has been released
      if (strcmp(getButtonName(pButtonCode),pButtonName) == 0 ){ continue;} 
		
      pButtonName = getButtonName(pButtonCode); 
		
		
	//Detect button pressed that's NOT a stop button "St"
      if (strcmp(getButtonName(pButtonCode),"St") != 0 && strcmp(getButtonName(pButtonCode),"") != 0){ 
	  //printf("\nYou have pressed %s \n",pButtonName);
	  
	  if(strcmp(pButtonName,"A") == 0) {pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects);} //create thread ON BULLET SHOT
	   
	  if(strcmp(pButtonName,"Joy-Pad RIGHT") == 0) {moveRight(&objects->allObjects[11],0,playerMoveSpeed);}
	  
	  if(strcmp(pButtonName,"Joy-Pad LEFT") == 0) {moveLeft(&objects->allObjects[11],0,playerMoveSpeed);}
	  
	  continue;
	}
		
        //Detect button pressed thats a stop button "St"
      else if (strcmp(getButtonName(pButtonCode),"St") == 0){ printf("\nDisplay Menu here with: PAUSE GAME,RESUME GAME,NEW GAME,QUIT\n");break;}
		
}

    pthread_join(playerBulletThread,NULL);

   
/* this portion is for testing at home only
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects); //create thread ON BULLET SHOT
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  //pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects); //create thread ON BULLET SHOT
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  
  pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects); //create thread ON BULLET SHOT
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects); //create thread ON BULLET SHOT
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  delay(3000);
  pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects); //create thread ON BULLET SHOT
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
 // moveLeft(&objects->allObjects[11],300,playerMoveSpeed);
  
  delay(6000);
  pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects); //create thread ON BULLET SHOT
  delay(6000);
  pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects); //create thread ON BULLET SHOT
  delay(6000);
  pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects); //create thread ON BULLET SHOT
  delay(6000);
  pthread_create(&playerBulletThread,&playerBulletThreadAttr,bulletRunner,objects); //create thread ON BULLET SHOT
  
  pthread_join(playerBulletThread,NULL);
  */
  //
  pthread_exit(0);
}

/**
 * This thread moves the monsters in a pattern
 */
void *monstersMovementRunner(void *param){
  struct allObj *objects;
  objects = param;
  
  pthread_t pawnsMovementThread;
  pthread_attr_t pawnsMovementThreadAttr;
  pthread_attr_init(&pawnsMovementThreadAttr);
  
  pthread_t knightsMovementThread;
  pthread_attr_t knightsMovementThreadAttr;
  pthread_attr_init(&knightsMovementThreadAttr);
  
  pthread_t queensMovementThread;
  pthread_attr_t queensMovementThreadAttr;
  pthread_attr_init(&queensMovementThreadAttr);
  
  pthread_create(&pawnsMovementThread,&pawnsMovementThreadAttr,pawnsMovementRunner,objects);
  pthread_create(&knightsMovementThread,&knightsMovementThreadAttr,knightsMovementRunner, objects);
  pthread_create(&queensMovementThread,&queensMovementThreadAttr,queensMovementRunner, objects);
    
  pthread_join(pawnsMovementThread,NULL);
  pthread_join(knightsMovementThread,NULL);
  pthread_join(queensMovementThread,NULL);
  
  pthread_exit(0);
}


/**
 * This thread moves pawns in a pattern
 */
void *pawnsMovementRunner(void *param){
  struct allObj *objects;
  objects = param;
  
  if(objects->state.gameOn){
  for(int i=0;i<5;i++){
      if(objects->state.gameOn){ moveAllRight(objects->pawns,8,400,10,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllDown(objects->pawns,1,400,10,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllLeft(objects->pawns,17,400,10,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllDown(objects->pawns,1,400,10,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllRight(objects->pawns,9,400,10,monstersMoveSpeed,&objects->state);}else{break;}
    }
  while(objects->state.gameOn){
      if(objects->state.gameOn){ moveAllRight(objects->pawns,8,300,10,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllLeft(objects->pawns,16,300,10,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllRight(objects->pawns,8,300,10,monstersMoveSpeed,&objects->state);}else{break;}
    }
  }
  
    pthread_exit(0);
  }

/**
 * This thread moves knights in a pattern
 */
void *knightsMovementRunner(void *param){
  struct allObj *objects;
  objects = param;
  if(objects->state.gameOn){
  for(int i=0;i<5;i++){
      if(objects->state.gameOn){ moveAllRight(objects->knights,8,400,5,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllDown(objects->knights,1,400,5,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllLeft(objects->knights,17,400,5,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllDown(objects->knights,1,400,5,monstersMoveSpeed,&objects->state);}else{break;}
      if(objects->state.gameOn){ moveAllRight(objects->knights,9,400,5,monstersMoveSpeed,&objects->state);}else{break;}
  }
  while(objects->state.gameOn){
	if(objects->state.gameOn){ moveAllRight(objects->knights,8,300,5,monstersMoveSpeed,&objects->state);}else{break;}
	if(objects->state.gameOn){ moveAllLeft(objects->knights,16,300,5,monstersMoveSpeed,&objects->state);}else{break;}
	if(objects->state.gameOn){ moveAllRight(objects->knights,8,300,5,monstersMoveSpeed,&objects->state);}else{break;}
    }
 }
  
  pthread_exit(0);
  
  }

/**
 * This thread moves queens in a pattern
 */
void *queensMovementRunner(void *param){
  struct allObj *objects;
  objects = param;
  
  pthread_t queen1MovementThread;
  pthread_attr_t queen1MovementThreadAttr;
  pthread_attr_init(&queen1MovementThreadAttr);
  
  pthread_t queen2MovementThread;
  pthread_attr_t queen2MovementThreadAttr;
  pthread_attr_init(&queen2MovementThreadAttr);
  
  pthread_create(&queen1MovementThread,&queen1MovementThreadAttr,queen1MovementRunner, objects);
  pthread_create(&queen2MovementThread,&queen2MovementThreadAttr,queen2MovementRunner, objects);
  
  pthread_join(queen1MovementThread,NULL);
  pthread_join(queen2MovementThread,NULL);
  
  pthread_exit(0);
  
  }

/**
 * This thread moves queen1 in a pattern
 */
void *queen1MovementRunner(void *param){
  struct allObj *objects;
  objects = param;
  
  while(objects->state.gameOn && objects->queens[0].active){
    if(objects->state.gameOn){for(int i=0;i<15;i++){if(objects->state.gameOn && objects->queens[0].active){moveRight(&objects->queens[0],40,monstersMoveSpeed);}}}else{break;}
    if(objects->state.gameOn){for(int j=0;j<30;j++){if(objects->state.gameOn && objects->queens[0].active){moveLeft(&objects->queens[0],40,monstersMoveSpeed);}}}else{break;}
    if(objects->state.gameOn){for(int k=0;k<15;k++){if(objects->state.gameOn && objects->queens[0].active){moveRight(&objects->queens[0],40,monstersMoveSpeed);}}}else{break;}
  }
  pthread_exit(0);
}
  
  /**
   * This thread moves queen 2 in a pattern
   */
void *queen2MovementRunner(void *param){
   struct allObj *objects;
   objects = param;
  
  while(objects->state.gameOn){
    if(objects->state.gameOn){for(int i=0;i<15;i++){if(objects->state.gameOn && objects->queens[1].active){moveLeft(&objects->queens[1],40,monstersMoveSpeed);}}}else{break;}
    if(objects->state.gameOn){for(int i=0;i<30;i++){if(objects->state.gameOn && objects->queens[1].active){moveRight(&objects->queens[1],40,monstersMoveSpeed);}}}else{break;}
    if(objects->state.gameOn){for(int i=0;i<15;i++){if(objects->state.gameOn && objects->queens[1].active){moveLeft(&objects->queens[1],40,monstersMoveSpeed);}}}else{break;}
  }
  pthread_exit(0);
}

/**
 * This thread is activated when a player shoots
 */
void playerShoot(struct objInfo *playerInfo,struct objInfo *shipBullet){

      if(!shipBullet->active){
	shipBullet->active = 1;
	int bulletXStart = (playerInfo->width/2 - shipBullet->width/2) + playerInfo->currentX;
	int bulletYStart =  playerInfo->currentY - (shipBullet->height + 5);
      
	shipBullet->currentX = bulletXStart;
	shipBullet->currentY = bulletYStart;
      
	printImage(bulletXStart,bulletYStart,shipBullet->pColorCodes,shipBullet->height,shipBullet->width,0);
	
	int quit=0;
	while(!quit && shipBullet->active){
	  quit = moveUp(shipBullet,playerBulletDelay,bulletMoveSpeed);
	  
	  }
	//quit is 1
	shipBullet->active = 0;
	clearImage(shipBullet,1);
		
      }
      
  }


/**
 * This function checks if knights are "exposed" and are free to shoot AT one momentout instance 
 */
void *updateExposedStatusRunner(void *param){
  struct allObj *objects;
   objects = param;
   
   //1.Check exposure of knights 
  while(objects->state.gameOn == 1){ //This loop can be a little slower on setting the EXPOSED value of knights because of 2 for loops. However it's fine for knights
    int exposedFlag;
    for(int i=0;i<5;i++){ //For each knight
    
      //Set up it's theoretical bullet coordinates
      
      exposedFlag = 1; //We assume a knight is exposed
    
      struct objInfo *currentKnight = &objects->knights[i];
	
      if(currentKnight->active == 1 && currentKnight->health > 0 ){ // Check if knight is active and worth checking
	
	//int xLeftLimitKnightBullet = ((currentKnight.width/2)-objects->allObjects[15].width/2) + currentKnight.currentX; // subtract width of bullet
	int xLeftLimitKnightBullet = ((currentKnight->width/2) - 2 ) + currentKnight->currentX; //line just for test
	//int xRightLimitKnightBullet = xLeftLimitKnightBullet + objects->allObjects[15].width; //add width of bullet
	int xRightLimitKnightBullet = xLeftLimitKnightBullet + 4; //line just for test


	for(int j=0;j<10;j++){ //For each pawn
	  
	  struct objInfo *currentPawn = &objects->pawns[j];
	  
	  int xLeftLimitPawn = currentPawn->currentX;
	  int xRightLimitPawn = xLeftLimitPawn + currentPawn->width;

	     
	  if(!(xRightLimitKnightBullet >= xLeftLimitPawn && xLeftLimitKnightBullet <= xRightLimitPawn)){ //Check if bullet of knight would be in a way of pawn
	    //If bullet isn't on the way, leave exposedFlag as 1
	    }else{ // If bullet is on the way of pawn
	      if(currentPawn->active == 0 && currentPawn->health == 0){exposedFlag = 0;} //If pawn is dead however, set knight to exposed
	      else{exposedFlag = 0;} //If pawn isn't dead, set knight to not exposed
	    }
	}
      }
      currentKnight->exposed = exposedFlag; //Set knight's final exposed value     
    }
  }
  pthread_exit(0);
}


/* RANDOM NUMBER GENERATOR WITHIN RANGE. SOURCE: https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range, User: Ryan Reich
 * Assumes 0 <= max <= RAND_MAX
 * Returns in the closed interval [0, max]
 */
long random_at_most(long max) {
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}


/**
 * This thread updates score displayed on the screen as player shoots the monsters
 */
void *scoreDisplayRunner(void *param){
  
   //Initialize info about digit images
   
    struct objInfo zeroDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(zeroDigit.width,zeroDigit.height,zeroDigit.image_pixels),
	  getPixelArray(zeroDigit.width,zeroDigit.height,clearDigit.image_pixels),zeroDigit.width,zeroDigit.height,-1,1,-1,-1,-1,-1};
	  
    struct objInfo oneDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(oneDigit.width,oneDigit.height,oneDigit.image_pixels),
	  getPixelArray(oneDigit.width,oneDigit.height,clearDigit.image_pixels),oneDigit.width,oneDigit.height,-1,1,-1,-1,-1,-1};
	  
    struct objInfo twoDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(twoDigit.width,twoDigit.height,twoDigit.image_pixels),
	  getPixelArray(twoDigit.width,twoDigit.height,clearDigit.image_pixels),twoDigit.width,twoDigit.height,-1,1,-1,-1,-1,-1};
    
    struct objInfo threeDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(threeDigit.width,threeDigit.height,threeDigit.image_pixels),
	  getPixelArray(threeDigit.width,threeDigit.height,clearDigit.image_pixels),threeDigit.width,threeDigit.height,-1,1,-1,-1,-1,-1};
	  
    struct objInfo fourDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(fourDigit.width,fourDigit.height,fourDigit.image_pixels),
	  getPixelArray(fourDigit.width,fourDigit.height,clearDigit.image_pixels),fourDigit.width,fourDigit.height,-1,1,-1,-1,-1,-1};
    
    struct objInfo fiveDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(fiveDigit.width,fiveDigit.height,fiveDigit.image_pixels),
	  getPixelArray(fiveDigit.width,fiveDigit.height,clearDigit.image_pixels),fiveDigit.width,fiveDigit.height,-1,1,-1,-1,-1,-1};
    
    struct objInfo sixDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(sixDigit.width,sixDigit.height,sixDigit.image_pixels),
	  getPixelArray(sixDigit.width,sixDigit.height,clearDigit.image_pixels),sixDigit.width,sixDigit.height,-1,1,-1,-1,-1,-1};
	  
    struct objInfo sevenDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(sevenDigit.width,sevenDigit.height,sevenDigit.image_pixels),
	  getPixelArray(sevenDigit.width,sevenDigit.height,clearDigit.image_pixels),sevenDigit.width,sevenDigit.height,-1,1,-1,-1,-1,-1};
	  
    struct objInfo eightDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(eightDigit.width,eightDigit.height,eightDigit.image_pixels),
	  getPixelArray(eightDigit.width,eightDigit.height,clearDigit.image_pixels),eightDigit.width,eightDigit.height,-1,1,-1,-1,-1,-1};
	  
    struct objInfo nineDigitInfo = {START_POS_BACKGROUND_x,START_POS_BACKGROUND_y,getPixelArray(nineDigit.width,nineDigit.height,nineDigit.image_pixels),
	  getPixelArray(nineDigit.width,nineDigit.height,clearDigit.image_pixels),nineDigit.width,nineDigit.height,-1,1,-1,-1,-1,-1};
	  
    
    struct objInfo digits[10];
    digits[0] = zeroDigitInfo;
    digits[1] = oneDigitInfo;
    digits[2] = twoDigitInfo;
    digits[3] = threeDigitInfo;
    digits[4] = fourDigitInfo;
    digits[5] = fiveDigitInfo;
    digits[6] = sixDigitInfo;
    digits[7] = sevenDigitInfo;
    digits[8] = eightDigitInfo;
    digits[9] = nineDigitInfo;
    
    struct allObj *objects;
    objects = param;
    
    while(objects->state.gameOn){
      
      //Calculate how many digits are in a score integer eg.10 => 2 , 204 => 3. max score is 300 so no need for further checks.
      int numDigits =1;

      if(objects->state.score >= 100){numDigits = 3;}
      else if(objects->state.score < 10){numDigits = 1;}
      else {numDigits = 2;}
  
      //Convert integer score to array of integers
      int score = objects->state.score;

      int arrOfDigits[numDigits]; //array of integers which is score
      
      if(score == 0){arrOfDigits[0] = 0;}

      int i = numDigits - 1;
      while (score > 0)
      {
        int digit = score % 10;
        score /= 10;
        arrOfDigits[i] = digit;
        //printf("digits[%d] = %d\n", i, arrOfDigits[i]);
        i--;
      }
      
      //Print the digits in appropriate spots
      int x = START_POS_BACKGROUND_x; //left corner of game map
      int y = START_POS_BACKGROUND_y;
      int x1 = 0;
      int x2 = 0;
      x1 = x + zeroDigitInfo.width ;
      x2 = x1 + zeroDigitInfo.width ;
      
         //Print the new digits to the screen
      if(numDigits == 1){
	int firstDigitToPrint = arrOfDigits[0];
	
	 printImage(x,y, digits[firstDigitToPrint].pColorCodes,zeroDigitInfo.height,zeroDigitInfo.width,0);
      }
      
      else if(numDigits == 2){
	int firstDigitToPrint = arrOfDigits[0];
	int secondDigitToPrint = arrOfDigits[1];
	
	printImage(0,0,digits[firstDigitToPrint].pColorCodes,zeroDigitInfo.height, zeroDigitInfo.width,0);
	printImage(x1,y, digits[secondDigitToPrint].pColorCodes, zeroDigitInfo.height,zeroDigitInfo.width,0);
      }
	
      else{
	int firstDigitToPrint = arrOfDigits[0];
        int secondDigitToPrint = arrOfDigits[1];
        int thirdDigitToPrint = arrOfDigits[2];
	
	printImage(x,y, digits[firstDigitToPrint].pColorCodes,  zeroDigitInfo.height, zeroDigitInfo.width,0);
	printImage(x1,y, digits[secondDigitToPrint].pColorCodes,  zeroDigitInfo.height, zeroDigitInfo.width,0);
	printImage(x2,y, digits[thirdDigitToPrint].pColorCodes,  zeroDigitInfo.height, zeroDigitInfo.width,0);
      }
      
      //
  
  }
    pthread_exit(0);
}



