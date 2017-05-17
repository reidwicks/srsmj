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


int lSpeed;
int rSpeed;
int baseSpeed = 50;

int futureError;
int error;

int kProportional = 0.05;
int kDerivative = 0.01;

int proportional;
int derivative;

int whitePixelCount;
int whiteThreshold = 127;

bool intersection = false;
bool lineLost = false;

int main(){
	init();
	
	while(intersection==false && lineLost==false){
		int pixel;
		whitePixelCount=0;
		error=0;
		futureError=0;
		
		take_picture();
		for(int i=0;i<319;i++){
			pixel=get_pixel(120,i,3);
			if (pixel>whiteThreshold){
				error += (i-160);
				whitePixelCount++;
			}
		}
		for(int i=0;i<319;i++){
			pixel=get_pixel(60,i,3);
			if (pixel>whiteThreshold){
				futureError += (i-160);
			}
		}
		printf("futureError: %d\n", futureError);
		printf("error: %d\n", error);
		proportional = error*kProportional;
		derivative = (futureError-error)*kDerivative;
		
		rSpeed = baseSpeed + proportional + derivative;
		lSpeed = baseSpeed - proportional - derivative;
		
		//Need to have functions to check for intersections here
		// --->
		
		if(whitePixelCount>0){
			set_motor(1,lSpeed);
			set_motor(2,rSpeed);
			}
		
	}
	
	return 0;
	}
