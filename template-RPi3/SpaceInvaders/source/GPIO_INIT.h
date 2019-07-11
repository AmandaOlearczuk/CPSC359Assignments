/**
 * Amanda Olearczuk
 * SNES driver for Raspberry Pi
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wiringPi.h>
#include <string.h>

#define CLK 11
#define LAT 9
#define DAT 10

unsigned int *gpio;				//base address	

unsigned int *gpioPtr(void);
void clear_GPIO(int pinNum);
void Init_GPIO(int pinNum,int functionCode);
void Write_Latch(int n);
void Write_Clock(int n);
void readPin(int pinNum);
int Read_Data();
int * Read_SNES();
char * getButtonName(int *pButtonCode);


/**
 * This function is for getting the base address (as seen on d2l)
 */
unsigned int *gpioPtr(void)
{
	int fdgpio = open("/dev/gpiomem", O_RDWR);
	
	if (fdgpio <0) {
		printf("unable to open");
	}
	
	unsigned int *gpio = (unsigned int *)mmap(0,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fdgpio,0);

	
	return gpio;
}

/**
 * This function clears the 3 bits associated with the pin
 */ 
void clear_GPIO(int pinNum){
	
	 *(gpio  + (pinNum/10)) = *(gpio  + (pinNum/10)) & ~(7<<((pinNum % 10) *3));
	}
	
/**
 *This function initializes a specific pin to a function 
 * for eg. Init_GPIO(12,001) sets pin 12 to 001 which is output 
*/
void Init_GPIO(int pinNum,int functionCode)
{
	switch(functionCode)
	{
		case 000 :
		//Input function
		//printf(">> Setting pin %d to %d. Current GPIO register of pin is: %d \n",pinNum,functionCode,*(gpio + (pinNum/10)));
		clear_GPIO(pinNum);
		//printf(">> New GPIO register of pin is: %d \n",*(gpio  + (pinNum/10)));
		break;
		  
		case 001 :
		//Output function
		//printf(">> Setting pin %d to %d. Current GPIO register of pin is: %d \n",pinNum,functionCode,*(gpio + (pinNum/10)));
		clear_GPIO(pinNum);
		*(gpio  + (pinNum/10)) |= (1 << ((pinNum % 10)*3));
		//printf(">> New GPIO register of pin is: %d \n",*(gpio  + (pinNum/10)));
		break;
		  
		case 100 :
		clear_GPIO(pinNum);
		*(gpio  + (pinNum/10)) |= (4 << ( ((pinNum % 10)*3)) );
		//Alt0
		break;
		  
		case 101 :
		clear_GPIO(pinNum);
		*(gpio + (pinNum/10)) |= (5 << ( ((pinNum % 10)*3)) ); 
		//Alt1
		break;
		  
		case 110 :
		clear_GPIO(pinNum);
		*(gpio  + (pinNum/10)) |= (6 << ( ((pinNum % 10)*3)) ); 
		//Alt2
		break; 
		  
		case 111 :
		clear_GPIO(pinNum);
		*(gpio  + (pinNum/10)) |= (7 << ( ((pinNum % 10)*3)) ); 
		//Alt3
		break; 
		  
		case 011 :
		clear_GPIO(pinNum);
		*(gpio + (pinNum/10)) |= (3 << ( ((pinNum % 10)*3)) ); 
	    //Alt4
		break;
		  
		case 010 :
		clear_GPIO(pinNum);
		*(gpio  + (pinNum/10)) |= (2 << ( ((pinNum % 10)*3)) );
		//Alt5
		break;
		
		default :
		printf("Invalid functionCode");
 	}
}		

/**
 * This function writes 0 or 1 bit to SNES LATCH line (pin 9)
 */
 void Write_Latch(int n){
	 
	 switch (n) {
		case 1 :
		//Writing 1
		gpio[7] = 1 << LAT;
	    break;
	    
	    case 0 :
	    //Writing 0
	    gpio[10] = 1 << LAT;
	    break;
	    
	    default:
	    printf("Incorrect latch bit to write \n");
	} 
} 
	 	
/**
 * This function writes 0 or 1 to SNES CLOCK line (pin 11)
 */	
void Write_Clock(int n){
		
	switch (n) {
		case 1 :
		//Writing 1
		gpio[7] = 1 << CLK;
	    break;
	    
	    case 0 :
	    //Writing 0
	    gpio[10] = 1 << CLK;
	    break;
	    
	    default:
	    printf("Incorrect clock bit to write \n");
	}

}

/**
 * This function reads and prints pin value
 */
void readPin(int pinNum){
	 	 int v = (gpio[13] >> pinNum) & 1 ;
	 	 printf("Pin value is: %d \n",v);
	 }
	
/**
 * This function reads bit from the data pin DTA
 */ 
int Read_Data(){
	 	 int v = (gpio[13] >> DAT) & 1 ;
	 	 return v;
	}

/**
 * This function reads SNES input and returns it as array of integers (its code)
 */
int * Read_SNES(){
	
	Write_Clock(1);            
	Write_Latch(1);           //Set latch line to high for 12us to latch button states in shift register
	delayMicroseconds(12);
	Write_Latch(0);
	
	static int buttonCode[16] ;
	int i = 0;
	while (i<16){
		delayMicroseconds(6);
		Write_Clock(0);          //Falling edge
		delayMicroseconds(6);
		int bitRead = Read_Data(); //Read bit from data line
		buttonCode[i] = bitRead;
		Write_Clock(1);           //Rising edge
		i++;                     //Go read next button
	}
	
	return buttonCode;

}

/**
 * This function gets button name based on button code.
 * Assumes only 1 button is pressed (so there's only one 0 in button code array)
 */
 
char * getButtonName(int *pButtonCode){
	
	char *buttonName = "";
	int indexOfKeyPressed = -1;
	
	for (int i=0;i<12;i++){

		if (pButtonCode[i] == 0){indexOfKeyPressed = i;break;}
	} 
	

	switch (indexOfKeyPressed)
	{
		case 0 : buttonName = "B"; break;
		case 1 : buttonName = "Y"; break;
		case 2 : buttonName = "Sl"; break;
		case 3 : buttonName = "St"; break;
		case 4 : buttonName = "Joy-pad UP"; break;
		case 5 : buttonName = "Joy-Pad DOWN"; break;
		case 6 : buttonName = "Joy-Pad LEFT"; break;
		case 7 : buttonName = "Joy-Pad RIGHT"; break;
		case 8 : buttonName = "A" ;break;
		case 9 : buttonName = "X" ;break;
		case 10 : buttonName = "L";break;
		case 11: buttonName = "R" ; break;
		default: break;
	}
	
	return buttonName;
	
	}


