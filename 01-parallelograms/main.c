#include <stdio.h>
#include <math.h>
#include <float.h>

#define EPS 1e5

int compare (double x, double y){
	if(fabs(x-y) < DBL_MIN){
		return fabs(x-y) <= DBL_EPSILON * DBL_MIN;
	}
	else{
		return fabs(x-y) <= EPS*DBL_EPSILON*fabs(x+y);
	}
}

double getX(double a, double b, double c, double k, double l, double m){
	double res;
	res = (b*m-l*c)/(a*l-b*k);
	return res;
}

double getY(double a, double b, double c, double k, double l, double m){
	double res;
	res = (k*c-a*m)/(a*l-b*k);
	return res;
}

void printObj(char obj){
	switch (obj){
		case 'c':
			printf("ctverec\n");
			break;
		case 'o':
			printf("obdelnik\n");
			break;
		case 'k':
			printf("kosoctverec\n");
			break;
		case 'r':
			printf("rovnobeznik\n");
			break;
	}
}

double param(double a, double b, double n1, double n2){
	double res;
	res = (-n1*a)+(-n2*b);
	return res;
}

int isInLine(double a, double b, double c, double xCoord, double yCoord){
	double expRes;
	expRes = fabs(a*(xCoord)+(b*yCoord));
	c = fabs(c);
	if(compare(fabs(expRes), fabs(c))){
		return 1;
	}
	else{
		return 0;
	}
}

char obrazec(double bX, double bY, double cX, double cY, double dX, double dY){

	double delkaBD = sqrt(fabs(bX-dX)*fabs(bX-dX)+fabs(bY-dY)*fabs(bY-dY));
	double delkaDC = sqrt(fabs(cX-dX)*fabs(cX-dX)+fabs(cY-dY)*fabs(cY-dY));
	double u1BD = dX-bX;
	double u2BD = dY-bY;
	double v1DC = cX-dX;
	double v2DC = cY-dY;
	
	if(compare(fabs(u1BD*v1DC), fabs(u2BD*v2DC))){
		if(compare(delkaBD, delkaDC)){
			return 'c';
		}
		else{
			return 'o';
		}
	}
	else{
		if(compare(delkaBD, delkaDC)){
			return 'k';
		}
		else{
			return 'r';
		}
	}
}

int main (void){
	
	double aX, aY, bX, bY, cX, cY;
	double a2X, a2Y, b2X, b2Y, c2X, c2Y; 
	char l, lbr, r, rbr;
	
	l = '[';
	r = ']';

	printf("Bod A:\n");
	if(scanf(" %c %lf , %lf %c", &lbr, &aX, &aY, &rbr) != 4 
	|| lbr != l 
	|| rbr != r){
		printf("Nespravny vstup.\n");
		return 1;
	}
	printf("Bod B:\n");
	if(scanf(" %c %lf , %lf %c", &lbr, &bX, &bY, &rbr) != 4
	|| lbr != l 
	|| rbr != r){
		printf("Nespravny vstup.\n");
		return 1;
	}
	printf("Bod C:\n");
	if(scanf(" %c %lf , %lf %c", &lbr, &cX, &cY, &rbr) != 4
	|| lbr != l 
	|| rbr != r){
		printf("Nespravny vstup.\n");
		return 1;
	}
	
	if(isInLine(-(bY-aY), (bX-aX), param(bX, bY, -(bY-aY), bX-aX), cX, cY)){
		printf("Rovnobezniky nelze sestrojit.\n");
	}
	else{
		a2X = getX(-(bY-aY), (bX-aX), param(cX, cY, -(bY-aY), (bX-aX)), -(cY-aY), (cX-aX), param(bX, bY, -(cY-aY), (cX-aX)));
		a2Y = getY(-(bY-aY), (bX-aX), param(cX, cY, -(bY-aY), (bX-aX)), -(cY-aY), (cX-aX), param(bX, bY, -(cY-aY), (cX-aX)));
	
		b2X = getX(-(bY-aY), (bX-aX), param(cX, cY, -(bY-aY), (bX-aX)), -(cY-bY), (cX-bX), param(aX, aY, -(cY-bY), (cX-bX)));
		b2Y = getY(-(bY-aY), (bX-aX), param(cX, cY, -(bY-aY), (bX-aX)), -(cY-bY), (cX-bX), param(aX, aY, -(cY-bY), (cX-bX)));
	
		c2X = getX(-(cY-aY), (cX-aX), param(bX, bY, -(cY-aY), (cX-aX)), -(cY-bY), (cX-bX), param(aX, aY, -(cY-bY), (cX-bX)));
		c2Y = getY(-(cY-aY), (cX-aX), param(bX, bY, -(cY-aY), (cX-aX)), -(cY-bY), (cX-bX), param(aX, aY, -(cY-bY), (cX-bX)));
		
		printf("A': [%.14g,%.14g], ", a2X, a2Y);
		printObj(obrazec(bX, bY, cX, cY, a2X, a2Y));
		printf("B': [%.14g,%.14g], ", b2X, b2Y);
		printObj(obrazec(aX, aY, cX, cY, b2X, b2Y));
		printf("C': [%.14g,%.14g], ", c2X, c2Y);
		printObj(obrazec(bX, bY, aX, aY, c2X, c2Y));
	}
	return 0;
}
