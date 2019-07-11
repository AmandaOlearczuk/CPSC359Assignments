/**
 * HEADER for checking various collisions happening in the game
 */
 
 


/**
 * This thread checks collisions happening with players bullet & other objects
 */
void *playerBulletCollisionsRunner(void *param){
  struct allObj *objects;
  objects = param;
  
  //1.Check for player's bullet collision with monsters and bricks
  while(objects->state.gameOn){
  if(objects->state.gameOn){playerBulletAndPawnsCheck(&objects->allObjects[12],objects->pawns,&objects->state);}
  if(objects->state.gameOn){playerBulletAndKnightsCheck(&objects->allObjects[12],objects->knights,&objects->state);}
  if(objects->state.gameOn){playerBulletAndQueensCheck(&objects->allObjects[12],objects->queens,&objects->state);}
  if(objects->state.gameOn){playerBulletAndBricksCheck(&objects->allObjects[12],objects->bricks,&objects->smallerBricks,&objects->state);}
  
  }
    pthread_exit(0);
  }
  
  /**
  * Thread checks for players bullet and bricks collision
  */

void playerBulletAndBricksCheck(struct objInfo *shipBullet,struct objInfo bricks[],struct replacementBricks *b,struct GameState *s){
   
  for(int i=0;i<3;i++){ //for each brick
    
    if(bricks[i].health>0 && bricks[i].active && shipBullet->active){
      if (shipBullet->currentY <= (bricks[i].currentY + bricks[i].height) && !((shipBullet->currentY + shipBullet->height) < (bricks[i].currentY))
      && shipBullet->currentX >= (bricks[i].currentX) && shipBullet->currentX<=(bricks[i].currentX+bricks[i].width)){
	
	shipBullet->active = 0;
	
	bricks[i].health -= 1;
	if(bricks[i].health == 0) {bricks[i].active = 0;clearImage(&bricks[i],1);} 
	
	 
	else if(bricks[i].health == 2) {
	  clearImage(&bricks[i],1);
	  changeObjImage(&bricks[i],b->pMediumBrickColorCodes,b->pMediumBrickClearColorCodes,b->mediumWidth,b->mediumHeight);
	  bricks[i].currentX +=6;
	  bricks[i].currentY +=4;
	  delay(50);
	  printImage(bricks[i].currentX ,bricks[i].currentY ,bricks[i].pColorCodes,bricks[i].height,bricks[i].width,0);
	    

	  }
	  
	else if(bricks[i].health == 1) {
	  clearImage(&bricks[i],1);
	  changeObjImage(&bricks[i],b->pSmallBrickColorCodes,b->pSmallBrickClearColorCodes,b->smallWidth,b->smallHeight);
	  bricks[i].currentX +=5;
	  bricks[i].currentY +=3;
	  delay(50);
	  printImage(bricks[i].currentX,bricks[i].currentY,bricks[i].pColorCodes,bricks[i].height,bricks[i].width,0);
	  }

	
      }
    }
    
  }
  }
  
  
/**
  * Function checks for players bullet and pawns collision
 */
void playerBulletAndPawnsCheck(struct objInfo *shipBullet,struct objInfo pawns[],struct GameState *s){
  
  for(int i=0;i<10;i++){
    
    if(pawns[i].health>0 && pawns[i].active && shipBullet->active){
      if (shipBullet->currentY <= (pawns[i].currentY + pawns[i].height) && !((shipBullet->currentY + shipBullet->height) < (pawns[i].currentY))
      && (shipBullet->currentX + shipBullet->width) >= (pawns[i].currentX) && shipBullet->currentX<=(pawns[i].currentX+pawns[i].width)
      && (shipBullet->currentX )>= (pawns[i].currentX) && shipBullet->currentX<=(pawns[i].currentX+pawns[i].width)){
	pawns[i].health = 0;
	pawns[i].active = 0;
	clearImage(&pawns[i],1);
	s->score+=5;
	
	shipBullet->active = 0;
      }
    }
  }
}

 /**
  * Function checks for players bullet and knights collision
  */
void playerBulletAndKnightsCheck(struct objInfo *shipBullet,struct objInfo knights[],struct GameState *s){
  
  for(int i=0;i<5;i++){
    
    if(knights[i].health>0 && knights[i].active && shipBullet->active){

      if (shipBullet->currentY <= (knights[i].currentY + knights[i].height) && !((shipBullet->currentY + shipBullet->height) < (knights[i].currentY))
      && (shipBullet->currentX + shipBullet->width )>= (knights[i].currentX) && shipBullet->currentX<=(knights[i].currentX+knights[i].width)
      && (shipBullet->currentX )>= (knights[i].currentX) && shipBullet->currentX<=(knights[i].currentX+knights[i].width)){
	knights[i].health -=1 ;
	if ((knights[i].health) == 0){knights[i].active = 0;s->score+=10;}
	clearImage(&knights[i],1);
      
	
	shipBullet->active = 0;
      }
    }
  }
  }
  
 /**
  * Function checks for players bullet and queens collision
  */
void playerBulletAndQueensCheck(struct objInfo *shipBullet,struct objInfo queens[],struct GameState *s){
  
  for(int i=0;i<2;i++){
    
    if(queens[i].health>0 && queens[i].active && shipBullet->active){

      if (shipBullet->currentY <= (queens[i].currentY + queens[i].height) && !((shipBullet->currentY + shipBullet->height) < (queens[i].currentY))
      && (shipBullet->currentX  + shipBullet->width)>= (queens[i].currentX) && shipBullet->currentX<=(queens[i].currentX+queens[i].width) 
      && (shipBullet->currentX )>= (queens[i].currentX) && shipBullet->currentX<=(queens[i].currentX+queens[i].width) ){
	queens[i].health -= 1 ;
	if ((queens[i].health) == 0){queens[i].active = 0;s->score+=100;delay(65);
	  printImage(queens[i].currentX, queens[i].currentY,queens[i].pClearColorCodes,queens[i].height,queens[i].width,0);printf("Image has been cleared \n");}
	
	printImage(queens[i].currentX, queens[i].currentY,queens[i].pClearColorCodes,queens[i].height,queens[i].width,0);
	
	shipBullet->active = 0;
      }
    }
  }
}



/**
 * This thread checks collisions happening with enemy's bullet and other objects
 */
void *enemiesBulletCollisionsRunner(void *param){
  struct allObj *objects;
  objects = param;
  
  while(objects->state.gameOn){ 
  if(objects->state.gameOn){enemiesBulletAndBricksCheck(objects->pawns,objects->bricks,&objects->state,10,&objects->enemyBullet,&objects->smallerBricks);}
  if(objects->state.gameOn){enemiesBulletAndBricksCheck(objects->knights,objects->bricks,&objects->state,5,&objects->enemyBullet,&objects->smallerBricks);}
  if(objects->state.gameOn){enemiesBulletAndBricksCheck(objects->queens,objects->bricks,&objects->state,2,&objects->enemyBullet,&objects->smallerBricks);}
  if(objects->state.gameOn){enemiesBulletAndPlayerCheck(objects->pawns,&objects->allObjects[11],&objects->state,10,&objects->enemyBullet);}
  if(objects->state.gameOn){enemiesBulletAndPlayerCheck(objects->knights,&objects->allObjects[11],&objects->state,5,&objects->enemyBullet);}
  if(objects->state.gameOn){enemiesBulletAndPlayerCheck(objects->queens,&objects->allObjects[11],&objects->state,2,&objects->enemyBullet);}
  if(objects->state.gameOn){queensBulletAndMonsterCheck(objects->queens,objects->knights,&objects->state,5,&objects->enemyBullet);}
  if(objects->state.gameOn){queensBulletAndMonsterCheck(objects->queens,objects->pawns,&objects->state,10,&objects->enemyBullet);}
  if(objects->state.gameOn){queensBulletAndMonsterCheck(objects->queens,objects->queens,&objects->state,2,&objects->enemyBullet);}

  }
    pthread_exit(0);
}

/**
 * This thread checks collision of queens bullet with any monsters
 */
void queensBulletAndMonsterCheck(struct objInfo *queens,struct objInfo *monster,struct GameState *game,int monsterCount,struct objInfo *bullet){
  
  for(int i=0;i<2;i++){ //for each queen
    if(queens[i].bulletActive){
      for(int j=0;j<monsterCount;j++){ //for each pawn/knight/otherqueen
    
	if(monster[j].health > 0 && monster[j].active ){// if queens bullet is fired, and if pawn/knight isn't dead already
	
	  if ((queens[i].bulletYCoordinate +bullet->height)>= (monster[j].currentY) && !((queens[i].bulletYCoordinate ) > (monster[j].currentY + monster[j].height)) //if bullet & pawn/knight/other queen collide
	  && queens[i].bulletXCoordinate + bullet->width >= (monster[j].currentX) && queens[i].bulletXCoordinate<=(monster[j].currentX + monster[j].width)){
	  
	    queens[i].bulletActive = 0;
	    
	    //delay(5);
	    //printImage(monster[i].currentX,monster[i].currentY,monster[i].pColorCodes,monster[i].height,monster[i].width, 1);
	
      
	}
      }
    }
  }
  }
}


/**
 * This function checks enemy's bullet and brick collision and does actions to respond to it
 */
void enemiesBulletAndBricksCheck(struct objInfo *monsterArray,struct objInfo *brickArray, struct GameState *gameState,int monsterCount,struct objInfo *bullet,struct replacementBricks *b){
  
    for(int i=0;i<3;i++){ //for each brick
    
    for(int j=0;j<monsterCount;j++){ //	for each monster
      
      if(monsterArray[j].bulletActive){ //if the monster has active bullet, examine that bullet
    
	if(brickArray[i].health>0 && brickArray[i].active){ //If the current brick is active
	  
	  if ((monsterArray[j].bulletYCoordinate + bullet->height >= (brickArray[i].currentY) && !((monsterArray[j].bulletYCoordinate > (brickArray[i].currentY + brickArray[i].height)))
	  && monsterArray[j].bulletXCoordinate+bullet->width >= (brickArray[i].currentX) && (monsterArray[j].bulletXCoordinate) <=(brickArray[i].currentX+brickArray[i].width))){ //If they collide
	
	    monsterArray[j].bulletActive = 0; //disable the bullet
	
	    brickArray[i].health -= 1;
	    
	    if(brickArray[i].health == 0) {brickArray[i].active = 0;clearImage(&brickArray[i],1);} //check if brick is dead too
	
	    else if(brickArray[i].health == 2) { //check if brick has health 2
	      clearImage(&brickArray[i],1);
	      changeObjImage(&brickArray[i],b->pMediumBrickColorCodes,b->pMediumBrickClearColorCodes,b->mediumWidth,b->mediumHeight);
	      brickArray[i].currentX +=6;
	      brickArray[i].currentY +=4;
	      delay(50);
	      printImage(brickArray[i].currentX ,brickArray[i].currentY ,brickArray[i].pColorCodes,brickArray[i].height,brickArray[i].width,0);
	    }
	  
	    else if(brickArray[i].health == 1) {
	      clearImage(&brickArray[i],1);
	      changeObjImage(&brickArray[i],b->pSmallBrickColorCodes,b->pSmallBrickClearColorCodes,b->smallWidth,b->smallHeight);
	      brickArray[i].currentX +=5;
	      brickArray[i].currentY +=3;
	      delay(50);
	      printImage(brickArray[i].currentX,brickArray[i].currentY,brickArray[i].pColorCodes,brickArray[i].height,brickArray[i].width,0);
	    }
	}
      }
    }
    }
  }
}

/**
 * This function checks collision with enemies bullet and a player
 */
void enemiesBulletAndPlayerCheck(struct objInfo *monsterArray,struct objInfo *playerShip,struct GameState *gameState,int monsterCount,struct objInfo *bullet){
  
  for(int j=0;j<monsterCount;j++){ //	for each monster
      
      if(monsterArray[j].bulletActive){ //if the monster has active bullet, examine that bullet
    
	if(playerShip->health>0 && playerShip->active){ //If the player is alive
	  
	  if ((monsterArray[j].bulletYCoordinate + bullet->height >= (playerShip->currentY) && !((monsterArray[j].bulletYCoordinate > (playerShip->currentY + playerShip->height)))
	  && monsterArray[j].bulletXCoordinate+bullet->width >= (playerShip->currentX) && (monsterArray[j].bulletXCoordinate) <=(playerShip->currentX+playerShip->width))){ //If they collide
	
	    monsterArray[j].bulletActive = 0; //disable the bullet
	    delay(10); //wait a bit for other threads to refresh
	    printImage(playerShip->currentX,playerShip->currentY,playerShip->pColorCodes,playerShip->height,playerShip->width,0); //re-print player to erase damages
	
	    if(playerShip->health == 3 || playerShip->health == 2) {playerShip->health -= 1;} //Decrease ship's live
	    else if(playerShip->health == 1){playerShip->health -= 1; playerShip->active = 0;} //Kill ship if lives are 0
	}
      }
    }
  }
}
