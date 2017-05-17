#include <stdio.h>
#include <time.h>
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

//just typing out code based on Elf's code to start, so we know we have something that works

int main(){
	init();
	while(true){
		take_picture();
		int error = 0;
		int white_no = 0; //number of white pixels
		int prop_sig = 0; //proportional signal
		float kp = 0.5;
		int i, w, s;
		double v_left, v_right;
		for(i=0; i<319; i++){
			w = get_pixel(120,i,3);
			if(w>127){
				s=1;
			}
			else{
				s=0;
			}
			error = error + (i-160) * s;
			prop_sig = (error*kp)/255;
			if(white_no > 0){
				v_left = 70 + prop_sig;
				v_right = 70 - prop_sig;
				set_motor(1, v_left);
				set_motor(2, v_right);
			}
			else{
				v_left = 70 - prop_sig;
				v_right = 70 + prop_sig;
				set_motor(1, v_left);
				set_motor(2, v_right);
			}
		}
	}
	return 0;
}
