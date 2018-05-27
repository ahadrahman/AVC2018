#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "E101.h"
#include <cmath>

int mode;
bool gateDone = false;
double prevError = 0;
double error;
double rateOfChange;
double turnDifference; //dv
double reactAmount = 0.01; //kp
double smoothAmount = 0.05; //kd MYSTERY

double speed = 50.0;
double leftSpeed;
double rightSpeed;

int thr;

const int SCREEN_HEIGHT = 240;
const int SCREEN_WIDTH = 320;


void drive(){
/*Takes arguments and uses them to control the motors */
		set_motor(1, rightSpeed);
		set_motor(2, leftSpeed*(-1));
}


void openGate(){
/*Connects to password server and sends password when required */

	char server[] = "130.195.6.196";

	while (!gateDone){
		//If connection to server is successful, send "Please", recive the password, and send the password
		if(connect_to_server(server, 1024) == 0){
			char message[] = "Please";
			if(send_to_server(message) == 0){
				receive_from_server(message);
				send_to_server(message);
				gateDone = true;
				mode = 1; //move to drive method
			}
		}	
	}
}

void readLine(){
	/*Takes input from the camera and sends instructions to drive method */

	error = 0;
	take_picture();

	//COMPUTE THE ERROR
	//Scan all the rows and find the min and max
	int scan_row = SCREEN_HEIGHT/2;
	int max = 0;
    int min = 255;
   	for (int i = 0; i < 320;i++){
		int pix = get_pixel(scan_row,i,3);
        if ( pix > max) {
			max = pix;
		}
		if (pix < min){
			min = pix;
		}
    }
    
    //Find the threshold
    thr = (max+min)/2;
    //printf(" min=%d max=%d threshold=%d\n", min, max,thr);
    
	
    int whi[320];  //array for white pixels
    for (int i = 0; i < 320;i++){
		whi[i]= 0 ;
		int pix = get_pixel(scan_row,i,3);
		if ( pix > thr)
		{
			whi[i] = 1;
		}
    }
    
    
    //switches to mode 2 if it finds that marker
    if (mode == 1){
		int sum = 0;
		for (int element = 0; element < 320; element++){
			sum = sum + abs(whi[element]);
		}
		if (sum > 300){ //all white
			mode = 2;
			return;
		}
	}
    
    

	//calculate the error
	double error = 0;
	for (int i = 0; i < 320; i++){
		error = error + (whi[i] * (i-160));
	}
	
	//calculate rateOfChange and call drive	
	rateOfChange = (error - prevError);
	float p_error = error * reactAmount;
	float d_error = rateOfChange * smoothAmount;
	turnDifference = p_error + d_error;
	leftSpeed = speed + turnDifference;
	rightSpeed = speed - turnDifference;
	printf("P: %f, D: %f", p_error, d_error);

	printf("LS: %.2f  RS: %.2f ", leftSpeed, rightSpeed);

	drive();
	
	prevError = error;

}

int scanHorizontal(){
	int horizontalPixels[SCREEN_WIDTH];
	for (int i=0; i<SCREEN_WIDTH; i++){
		horizontalPixels[i] = 0;
		int pixLeft = get_pixel(20, i, 3);
		if (pixLeft > thr){
			horizontalPixels[i] = 1;
		}
	}
	int sum = 0;
	for (int j=0; j < SCREEN_WIDTH; j++){
		sum = sum + horizontalPixels[j];
	}
	return sum;
}





//scans the left part of the image. returns a value based on how much white is in that column
int scanLeft(){
	int leftPixels[240];
	for (int i=0; i<240; i++){
		leftPixels[i] = 0;
		int pixLeft = get_pixel(i, 40, 3);
		if (pixLeft > thr){
			leftPixels[i] = 1;
		}
	}
	int sum = 0;
	for (int j=0; j < 240; j++){
		sum = sum + leftPixels[j];
	}
	return sum;
}

//scans the right part of the image. returns a value based on how much white is in that column
int scanRight(){
	int rightPixels[240];
	for (int i=0; i<240; i++){
		rightPixels[i] = 0;
		int pixRight = get_pixel(i, 280, 3);
		if (pixRight > thr){
			rightPixels[i] = 1;
		}
	}
	int sum = 0;
	for (int j=0; j < 240; j++){
		sum = sum + rightPixels[j];
	}
	return sum;
}


void turnLeft(){ //turn left 90d
	set_motor(1, 35);
	set_motor(2, 0);
	sleep1(1,500000);
	set_motor(1, 0);
	return;
}

void turnRight(){ //turn right 90d
	set_motor(2, 35);
	set_motor(1, 0);
	sleep1(1,500000);
	set_motor(2, 0);
	return;
}

void turnAround(){
	set_motor(1, 65);
	set_motor(2, 0);
	sleep1(1, 0);
	set_motor(1, 0);
	return;
}



void lineMaze(){
	
	if (scanHorizontal() > 10) {
		readLine();
		return;
	}
	else { 
		if (scanLeft() > 10){ //found some white on left side
			turnLeft();
		}
		else { //found no white
			if (scanRight() > 10){ //found some white on right side
				turnRight();
			}
			else {
				turnAround();
			}
		}
	}
	
	readLine();
	
}


int main (){
/* Contains logic to run the right methods at the right time/stage */
init(); 
	
mode = 0; //starts at network gate
while(1){
	printf("MODE: %d", mode);
	switch (mode){
		case 0: openGate(); //quadrant 1
		case 1: readLine(); //quadrant 2
		case 2: lineMaze(); //quadrant 3 yeet
		//case 3: readWall(); //quadrant 4
	}
}
return 0;
}

