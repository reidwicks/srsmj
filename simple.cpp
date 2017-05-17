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

int futureError;
int error;

double kProportional = 0.007;

double proportional;

int whitePixelCount;
double whiteThreshold = 100;

bool intersection = false;
bool lineLost = false;

int quad1(){
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
			//printf("whitePixelCount: %d\n", whitePixelCount);
		}
		printf("error: %d\n", error);
		proportional = error*kProportional;
		
		rSpeed = 165 -proportional;
		lSpeed = 165 +proportional;
		
		//Need to have functions to check for intersections here
		// --->
		
		if(whitePixelCount>0){
			set_motor(1,lSpeed);
			set_motor(2,rSpeed);
			}
		else{
			set_motor(1, -200);
			set_motor(2, -200);

		}
		
	}
	stop(1);
	stop(2);
}

int main(){
	init();
	quad1();
	
	return 0;
	}
