/**
 * HEADER for functions that move the objects in the game
 */


/**
 * This function moves an image to the right with speed d
 */
void moveRight(struct objInfo *info,int d,int speedOfMovement){
    delay(d); 
    int quit =0;
    printImage(info->currentX,info->currentY,info->pClearColorCodes,info->height,info->width,1); //black out the image
    quit = printImage(info->currentX + speedOfMovement,info->currentY,info->pColorCodes,info->height,info->width,1); //move it right
  
    if(quit){ //check if image was printed out of bounds
      printImage(info->currentX + speedOfMovement ,info->currentY,info->pClearColorCodes,info->height,info->width,1); //black out the image
      printImage(info->currentX,info->currentY,info->pColorCodes,info->height,info->width,1);
      return;}
    info->currentX  = info->currentX + speedOfMovement; 
    
  }
  
  /**
   * This function moves all images in array to the right , some x amount of times
   */
 void moveAllRight(struct objInfo *array,int howManyTimes,int delayAmount,int objCount,int speedOfMovement,struct GameState *game){
  for(int i=0;i<howManyTimes;i++){
    delay(delayAmount);
    for(int i=objCount-1;i>=0;i--){
      if(array[i].health !=0 && array[i].active && game->gameOn){ //if obj isn't dead,move it
	//printf("moving monster # %d \n",i);
	    moveRight(&array[i],0,speedOfMovement);
      }
      
    }
  }
}

/**
 * Moves all images in array to the left, some x amount of times
 */
void moveAllLeft(struct objInfo *array,int howManyTimes,int delayAmount,int objCount,int speedOfMovement,struct GameState *game){
  for(int i=0;i<howManyTimes;i++){
    delay(delayAmount);
    for(int i=0;i<objCount;i++){
      if(array[i].health !=0 && array[i].active && game->gameOn){ //if obj isn't dead,move it
	    moveLeft(&array[i],0,speedOfMovement);
      }
    }
  }
}

/**
 * Moves all images in array down , some x amount of times
 */
void moveAllDown(struct objInfo *array, int howManyTimes,int delayAmount,int objCount,int speedOfMovement,struct GameState *game){
  for(int i=0;i<howManyTimes;i++){
    delay(delayAmount);
    for(int i=0;i<objCount;i++){
	if(array[i].health !=0 && array[i].active && game->gameOn){ //if obj isn't dead,move it
	    moveDown(&array[i],0,speedOfMovement);
	}
    }
  }
}

/**
 * Moves an image down, with some d speed
 */
void moveDown(struct objInfo *info,int d,int speedOfMovement){
  
    delay(d); 
    int quit =0;
    printImage(info->currentX,info->currentY,info->pClearColorCodes,info->height,info->width,1); //black out the image
    quit = printImage(info->currentX ,info->currentY+ speedOfMovement,info->pColorCodes,info->height,info->width,1); //move it down
  
    if(quit){ //check if image was printed out of bounds
      printImage(info->currentX,info->currentY + speedOfMovement,info->pClearColorCodes,info->height,info->width,1); //black out the image
      printImage(info->currentX,info->currentY,info->pColorCodes,info->height,info->width,1);
      return;}
    info->currentY  = info->currentY + speedOfMovement; 
  
  }
  
/**
 * Moves image left with some speed d
 */
void moveLeft(struct objInfo *info,int d,int speedOfMovement){
    delay(d); 
    int quit =0;
    printImage(info->currentX,info->currentY,info->pClearColorCodes,info->height,info->width,1); //black out the image
    quit = printImage(info->currentX - speedOfMovement,info->currentY,info->pColorCodes,info->height,info->width,1); //move it left
    
    if(quit){ //check if image was printed out of bounds
      printImage(info->currentX - speedOfMovement,info->currentY,info->pClearColorCodes,info->height,info->width,1); //black out the image
      printImage(info->currentX,info->currentY,info->pColorCodes,info->height,info->width,1);
      return;}
    info->currentX  = info->currentX - speedOfMovement; 
    
  }

/**
 * Moves image up with some speed d
 */
int moveUp(struct objInfo *info,int d,int speedOfMovement){
    delay(d); 
    int quit =0;
    printImage(info->currentX,info->currentY,info->pClearColorCodes,info->height,info->width,1); //black out the image
    quit = printImage(info->currentX ,info->currentY - speedOfMovement,info->pColorCodes,info->height,info->width,1); //move it down
  
    if(quit){ //check if image was printed out of bounds
      printImage(info->currentX,info->currentY - speedOfMovement,info->pClearColorCodes,info->height,info->width,1); //black out the image
      printImage(info->currentX,info->currentY,info->pColorCodes,info->height,info->width,1);
      return quit;}
    info->currentY  = info->currentY - speedOfMovement; 
    return quit;
  }
