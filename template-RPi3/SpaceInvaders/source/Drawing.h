#include "declarations.h"
#include "constants.h"
/**
 * HEADER for drawing various images on the screen, & clearing them
 */



/**
 * Draw a pixel on the screen
 */
void drawPixel(struct Pixel *pixel){

	//find address of pixel in framebuffer and put color there

	int offset = (pixel->y * frameBufferStruct.x) + pixel->x;
	frameBufferStruct.fptr[offset] = pixel ->color; //address of pixel 

}

/** This function moves pixel to the right
 *  1 indicates that printing out of bounds was attempted
 */
int updateVerLoc(struct Pixel *pixel){
       int quit =0;
       pixel->y +=1;
	if (pixel->y >= END_POS_BACKGROUND_y || pixel->y <= START_POS_BACKGROUND_y) quit =1;
	return quit;
	
}

/**
 * This function moves pixel down
 * 1 indicates printing out of bounds was attempted
 */
int updateHorLoc(struct Pixel *pixel){
	int quit=0;
	pixel->x +=1;
	if (pixel->x >= END_POS_BACKGROUND_x || pixel->x <= START_POS_BACKGROUND_x) quit =1;
	return quit;
}

/**
 * This function simulates clearing of a pixel so it sets a pixel to black
 */
void clearPixel(struct Pixel *pixel){
	int offset = (pixel->y * frameBufferStruct.x) + pixel->x;
	frameBufferStruct.fptr[offset] = 0x000000; //replace pixel with black(clear)
}

  /**
   * This function prints image defined by pixel color array of size Imgwidth*Imgheight
   * 1 indicates that printing out of bounds was attempted
   */ 
int printImage(int xCoordinate,int yCoordinate,long long *pixelColorCodes,int imgHeight,int imgWidth, int boundsEnable){

    
    int quit = 0;
    struct Pixel *pixel;
    pixel = malloc(sizeof(struct Pixel));
    pixel->x = xCoordinate;
    pixel->y = yCoordinate;
	
    int c=0;
	for (int j=0;j<imgHeight;j++){
	  for(int i=0;i<imgWidth;i++){
	    pixel->color = pixelColorCodes[c];
	    c++;
	    drawPixel(pixel);
	    quit = updateHorLoc(pixel);
	    if(boundsEnable){
	       if(quit == 1){return quit;}
	     }
	  }
	  pixel->x = xCoordinate;
	  quit = updateVerLoc(pixel);
	  if(boundsEnable){
	     if(quit == 1){return quit;}
	   }
	}
	
	return quit;
    }

/**
 * This function returns array of pixel values of image of size width*height
 */
long long *getPixelArray(int width, int height, const unsigned char *pImg){
 
    long long *pixelColorCodes = malloc (sizeof (long long) * (width*height)); //DO THIS WHEN GETTING LOCAL VAR RETURNED POINTER
    
    int c = 0;
    long long A[4];
    
    for(int l=0;l<(width*height*4);l+=4){
	  
      long long size = 4;
      long long i;
      long long j;
      long long n;
      long long k;

      i = size;
      j = 0;
      n = 0;
      k = 1;
	  
      A[0] = *(pImg+l);
      A[1] = *(pImg+l+1);
      A[2] = *(pImg+l+2);
      A[3] = *(pImg+l+3);
      
      while( 1)
      {
	if( j == 0 )
	{
	  i--;
	  if( i < 0 )
	  {	
	    break;
	  }
	  j = A[ i ];
	}	

	  n += ( j % 10 ) * k;
	  j /= 10;
	  k *= 10;
      }

      pixelColorCodes[c] = n;
      c++;
    }

    return pixelColorCodes;

  }
  
/**
 * This function gives new image definition to an object
 */
void changeObjImage(struct objInfo *info,long long *pixelColorCodesImg,long long *pixelColorCodesClearImg,int w,int h){
    info->pColorCodes = pixelColorCodesImg;
    info->pClearColorCodes = pixelColorCodesClearImg;
    info->width = w;
    info->height = h;
}

/**
 * This function simulates clearing of an image - replaces it's pixels with black color
 */
void clearImage(struct objInfo *obj,int respectBounds){
   printImage(obj->currentX,obj->currentY,obj->pClearColorCodes,obj->height,obj->width,respectBounds); //black out the image
   
  }
