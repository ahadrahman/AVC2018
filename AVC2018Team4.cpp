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
bool gateDone = false;
double prevError = 0;
double error;
double rateOfChange;
double turnDifference; //dv
double reactAmount = 0.005; //kp
double smoothAmount = 0.5; //kd MYSTERY
double speed = 40.0;
double leftSpeed;
double rightSpeed;

void drive(){
/*Takes arguments and uses them to control the motors */

turnDifference = (error * reactAmount) + (rateOfChange * smoothAmount);
leftSpeed = speed + turnDifference;
rightSpeed = speed - turnDifference;

set_motor(1, rightSpeed);
set_motor(2, leftSpeed*(-1));
}

int readLine(){
/*Takes input from the camera and sends instructions to drive method */

error = 0;
take_picture();

//COMPUTE THE ERROR
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

	//calculate the error
	double error = 0;
	for (int i = 0; i < 320; i++){
		error = error + (whi[i] * (i-160));
	}
	
	//calculate rateOfChange and call drive	
	rateOfChange = error - prevError / 0.1;
	drive();
	prevError = error;

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

void openGate(){
/*Connects to password server and sends password when required */

char server[] = "130.195.6.196";

if (!gateDone){
	//If connection to server is successful, send "Please", recive the password, and send the password
	if(connect_to_server(server, 1024) == 0){
		char message[] = "Please";
		if(send_to_server(message) == 0){
			receive_from_server(message);
			send_to_server(message);
			//done = true;
			//return done;
			gateDone = true;
			mode = 1; //move to drive method
		}
	}	
}
}

int modeChecker(){
/*Works out whether we are in the first stage (single line), second stage, (line maze),
* or third stage (walled maze). Returns current stage. This will be used to decide
* whether the readLine or findPath methods will control the motors, and then switching
* to readWall when we reach that stage 
* network gate: 0, curvy line: 1, maze line: 2, walled maze: 3*/

int stage = 1; ////set at 1 for testing purposes

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
