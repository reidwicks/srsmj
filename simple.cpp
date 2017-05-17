#include <stdio.h>
#include "e101.h"

int lSpeed;
int rSpeed;
int baseSpeed = 80;

int futureError;
int error;

int kProportional;
int kDerivative;

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
		for(int i=0;i<320;i++){
			pixel=get_pixel(i,120,3);
			if (pixel>threshold){
				error += (i-160);
				whitePixelCount++;
			}
		}
		for(int i=0;i<320;i++){
			pixel=get_pixel(i,60,3);
			if (pixel>threshold){
				futureError += (i-160);
			}
		}
		proportional = error*kProportional;
		derivative = (futureError-error)*kDerivative;
		
		rSpeed = baseSpeed - proportional - derivative;
		lSpeed = baseSpeed + proportional + derivative;
		
		//Need to have functions to check for intersections here
		// --->
		
		if(whitePixelCount>0){
			set_motor(1,lSpeed);
			set_motor(2,rSpeed);
			}
		
	}
	
	return 0;
	}
