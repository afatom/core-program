#include <stdio.h>
#include "point.h"


int main (void)
{
	Point p1,p2;
	//before init
	p1.PrintPoint();
	p2.PrintPoint();
	
	//init
	p1.Init();
	p2.Init();
	
	//after init
	p1.PrintPoint();
	p2.PrintPoint();
	
	
	
	return 0;
}
