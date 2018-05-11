#include  <stdio.h>
#include <time.h>
#include "E101.h"

/* Automated Vehicle Challenge 2018, Team 4
 * ENGR101, trimester 1
 * 
 * Team lead: Ahad Rahman
 * Software lead: Alex Pace
 * Software: Dejene Kumela, Marcus Rathod
 * Hardware: Sean Osborne-Curtis
 * 
 * GitHub repo: https://github.com/ahadrahman/AVC2018
 */

int mode;
double error;

void drive(char direction, int speed){
/*Takes arguments and uses them to control the motors */

}

int readLine(){
/*Takes input from the camera and sends instructions to drive method */

//Arthur's code *uwu*

//Scan all the rows and find the min and max
int scan_row = 160;
int max = 0;
    int min =255;
   	for (int i = 0; i <320;i++){
		int pix = get_pixel(scan_row,i,3);
        if ( pix > max) {
			max = pix;
		}
		if (pix < min){
			min =pix;
		}
    }
    
    //Find the threshold
    int thr = (max+min)/2;
    printf(" min=%d max=%d threshold=%d\n", min, max,thr);
    
    int whi[320];  //array for white pixels
    for (int i = 0; i <320;i++){
		whi[i]= 0 ;
		int pix = get_pixel(scan_row,i,3);
		if ( pix > thr)
		{
			whi[i] = 1;
		}
    }

//our code
double error = 0;
	for (int i = 0; i < 320; i++){
		error = error + (pixelLine[i] * (i-160));
	}

return 0;
}

int readWall(){
/*Takes input from the infra-red sensors and sends instructions to drive method */

return 0;
}

int findPath(){
/*Takes input from readLine and works out the correct path forward, then
 * passes instructions to drive method */

return 0;
}

bool openGate(){
/*Connects to password server and sends password when required */
bool done = false;

return done;
}

int modeChecker(){
/*Works out whether we are in the first stage (single line), second stage, (line maze),
* or third stage (walled maze). Returns current stage. This will be used to decide
* whether the readLine or findPath methods will control the motors, and then switching
* to readWall when we reach that stage 
* network gate: 0, curvy line: 1, maze line: 2, walled maze: 3*/
int stage = 1; //set at 1 for testing purposes

return stage;
}

int main (){
/* Contains logic to run the right methods at the right time/stage */
init(); 
	
mode = modeChecker();
while(1){
	switch (mode){
		case 0: openGate();
		case 1: readLine();
		case 2: findPath();
		case 3: readWall();
	}
}

return 0;
}
