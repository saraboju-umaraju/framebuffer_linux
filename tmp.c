#include <stdio.h>
#include <math.h>

int main (int argc, char *argv[])
{
	int y = 768 ;	
	int x = 1366 ;
	long double xx = 0;
	int k=0;
	int l=0;
	float xpos,ypos,radsqr,xsqr;
	int radius = 25 ;
	for(k=0; k<y; k++) {

		radsqr = pow(radius,2);
		xsqr = pow(k,2);
		ypos = sqrt(abs(radsqr - xsqr));
		printf("%d\n", k);
		printf("%f\n", ypos);
	}
}

