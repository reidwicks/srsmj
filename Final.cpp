#include <stdio.h>
#include "E101.h"

/*----------------------------/
 * AVC Project Team Serious Mojo (SRSMJ)
 * 
 * Shadrach Luke Hargreaves
 * Reid Alexander Wicks
 * Sean Naylor
 * Max Watson
 * Josh Bolitho
 **/

/* motor 1 = left hand side
 * motor 2 = right hand side 
**/


double lSpeed;
double rSpeed;
int baseSpeed = 70;

int futureError;
int futureCount;

int currentError;
int currentCount;

int leftCount;
int rightCount;
int topCount;

bool leftDetected;
bool rightDetected;
bool topDetected;


double kProportional = 0.007;
double kDerivative = 0.007;// replace with 0.007 if it doesn't work


int proportional;
int derivative;

int whiteThreshold = 100;

int quad = 1;

int widthThreshold = 50;

int openGate(){
	while(true){
		connect_to_server("130.195.006.196",1024);
		char* serverMessage = new char[24];
		send_to_server("Please");
		receive_from_server(serverMessage);
		if(serverMessage!= NULL){
			printf(serverMessage);
			send_to_server(serverMessage);
			break;
			}
		}
	sleep1(0,500000);
	}

int goLeft(){
	set_motor(1,255);
	set_motor(2,255);
	sleep1(0,10000);
	
	set_motor(2,200);
	set_motor(1,240);
	sleep1(2,200000);
	
	set_motor(2,255);
	sleep1(0,10000);
	return 0;
	}
int goForwards(){
	set_motor(1,255);
	set_motor(2,255);
	sleep1(0,10000);
	
	set_motor(1,200);
	set_motor(2,200);
	sleep1(1,0);
	set_motor(1,255);
	set_motor(2,255);
	sleep1(0,10000);
	return 0;
	}

int turnAround(){
	set_motor(1,255);
	set_motor(2,255);
	sleep1(0,10000);
	
	set_motor(1,200);
	set_motor(2,-200);
	sleep1(1,880000);
	set_motor(1,255);
	set_motor(2,255);
	sleep1(0,10000);
	return 0;
	}

int intersection(){
	leftDetected = false;
	rightDetected = false;
	topDetected = false;
	
	if(leftCount >= widthThreshold){
		leftDetected = true;
		}
	if(rightCount >= widthThreshold){
		rightDetected = true;
		}
	if(futureCount >= widthThreshold){
		topDetected = true;
		}
	
	if(leftDetected && rightDetected ){
		goLeft();
		}
	if(!leftDetected && !rightDetected && !topDetected){
		turnAround();
		}
	if(!leftDetected && topDetected){
		goForwards;
		}
		
	
	
	return 0;
	}


int main(){
	init();
	sleep1(10,0);
	openGate();
	
	
	while(quad==1){
		
		int pixel;
		
		currentError=0;
		futureError=0;
		currentCount=0;
		futureCount=0;
		leftCount=0;
		rightCount=0;
		topCount=0;
		
		take_picture();
		
		// Current error & count - Middle line - 1/2
		for(int i=0;i<320;i++){
			pixel=get_pixel(120,i,3);
			if (pixel>whiteThreshold){
				currentError += (i-160);
				currentCount++;
			}
		}
		
		// Future error & count - Future line - 3/4
		for(int i=0;i<320;i++){
			pixel=get_pixel(180,i,3);
			if (pixel>whiteThreshold){
				futureError += (i-160);
				futureCount++;
			}
		}
		
		// right Counter - check for white pixels down right column
		for(int i=0;i<240;i++){
			pixel=get_pixel(i,10,3);
			if (pixel>whiteThreshold){
				rightCount++;
			}
		}
		
		// left Counter - check for white pixels down left column
		for(int i=0;i<240;i++){
			pixel=get_pixel(i,230,3);
			if (pixel>whiteThreshold){
				leftCount++;
			}
		}
		
		// top Counter - check for white pixels along top row
		for(int i=0;i<320;i++){
			pixel=get_pixel(230,i,3);
			if (pixel>whiteThreshold){
				topCount++;
			}
		}
		//printf("leftCount: %d\n",leftCount);
		//printf("rightCount: %d\n",rightCount);
		//printf("topCount: %d\n",topCount);
		//printf("currentCount: %d\n",currentCount);
		//printf("futureCount: %d\n",futureCount);
		
		//printf("futureError: %d\n",futureError);
		//printf("currentError: %d\n", currentError);
		
		proportional = currentError*kProportional;
		//derivative = (currentError-futureError)*kDerivative;
		derivative =0;
		
		rSpeed = (255-baseSpeed) - proportional - derivative;
		lSpeed = (255-baseSpeed) + proportional + derivative;
		
		//Need to have functions to check for intersections here
		// --->
		
		if(currentCount>0){
			set_motor(1,lSpeed);
			set_motor(2,rSpeed);
			}
		else{
			set_motor(1, -200);
			set_motor(2, -200);

		if()
		
		}
		
	}
	set_motor(1, -255);
	set_motor(2, -255);
	
	return 0;
	}
