#include <stdio.h>
#include "E101.h"

int main(){
	init();
	set_motor(1, 0);
	set_motor(2, 0);
	stop(1);
	stop(2);
	return 0;
}
