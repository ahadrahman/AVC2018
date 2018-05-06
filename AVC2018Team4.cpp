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


int main (){
/* Contains logic to run the right methods at the right time/stage */

return 0;
}

void drive(char direction, int speed){
/*Takes arguments and uses them to control the motors */

}

int readLine(){
/*Takes input from the camera and sends instructions to drive method */

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
* to readWall when we reach that stage*/
int stage = 0;

return stage;
}
