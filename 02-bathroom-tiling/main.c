#include <stdio.h>
#include <math.h>
#include <assert.h>

#define MAX_SIZE 1e7

/*--------------------
Returns greatest common divisor of two numbers
using Euclidean algorithm.
----------------------
The parameters are the two numbers for calculating
the greatest common divisor of those numbers. 
----------------------*/
int gcd(int x, int y){
  int tmp;
  while(y != 0){
    tmp = y;
    y = x % y;
    x = tmp;
  }
  return x;
}

/*--------------------
Returns least common multiple of two numbers.
----------------------
The parameters are the two numbers for calculating
the least common multiple of those numbers. 
----------------------*/
int lcm(int x, int y){
	return fabs(x * y) / gcd(x, y);
}

/*--------------------
Returns true if the number is more accurate than 1 mm,
otherwise returns false.
----------------------
The parameter is the number.  
----------------------*/
int isTooAccurate(double x){
	return (0 != x * 10 - (int)(x * 10));
}

/*--------------------
Returns minimal possible size above minumum width/length.
----------------------
First parameter is the current tile size.
Second parameter is the current joint size.
Third parameter is the minimal width/length.
----------------------*/
int sizeAboveMinimum(int tile, int joint, int minSize){              //<--------- DO THIS
	int cycle = 1;
	int tmp = 0;
	while(1){
		if(tmp >= minSize){
			return tmp;
		}
		if(cycle == 1){
			tmp += joint;	
		}
		else{
			tmp += joint+tile;
		}
		cycle++;	
	}
}

/*--------------------
Returns minimal dimension of the room without
cutting the tiles.
If the dimension is larger than MAX_SIZE(10000000),
the function returns -1.
----------------------
First parameter is the current tile size.
Second parameter is the current joint size.
Third parameter is the size calculated in previous cycle.
Fourth parameter is the least common multiple (tile+joint)
calculated in previous cycle.
Fifth parameter is minimal width/length.
----------------------*/
int calcSize(int tile, int joint, int lastSize, int lastLcm, int minValue){

	int diff = lcm(lastLcm, tile+joint);
	int tmp = diff;
	int cycle = 1;
	
	while(1){
		if(tmp > MAX_SIZE*10){
			return -1;
		}
		if((tmp-lastSize)%lastLcm == 0 && tmp != diff && tmp-diff > minValue){
			return tmp-diff;
			break;
		}
		if(cycle == 1)
			tmp += joint;
		else
			tmp += tile+joint;
		cycle++;
	}
}

int main(void){
	
	double minRoomLength = 0;
	double minRoomWidth = 0;
	double tileSize = 0;
	double jointSize = 0;
	double lastLength = 0;
	double lastWidth = 0;
	int lastLcm = 0;
	int cycle = 0;
	
	//assert(237005 == calcSize(101, 2, 4730, 12225, 2000));

	printf("Minimalni velikost:\n");
	if(scanf("%lf %lf", &minRoomWidth, &minRoomLength) != 2
			|| minRoomWidth > MAX_SIZE
			|| minRoomLength > MAX_SIZE
			|| minRoomWidth <= 0
			|| minRoomLength <= 0
			|| isTooAccurate(minRoomWidth)
			|| isTooAccurate(minRoomLength)){
		printf("Nespravny vstup.\n");
		return 1;
	}
	
	minRoomWidth *= 10;
	minRoomLength *= 10;
	
	printf("Dlazdicky:\n");
	while(!feof(stdin)){
		++cycle;
		if(scanf("%lf %lf\n", &tileSize, &jointSize) != 2
				|| tileSize > MAX_SIZE
				|| jointSize > MAX_SIZE
				|| tileSize <= 0
				|| jointSize < 0
				|| isTooAccurate(tileSize)
				|| isTooAccurate(jointSize)){
			printf("Nespravny vstup.\n");
			return 1;		
		}
		tileSize *= 10;
		jointSize *= 10;
		
		if(cycle == 1){
			lastWidth = sizeAboveMinimum(tileSize, jointSize, minRoomWidth);
			lastLength = sizeAboveMinimum(tileSize, jointSize, minRoomLength);
			lastLcm = (int)(tileSize + jointSize);
		}
		else{
			lastWidth = calcSize(tileSize, jointSize, lastWidth, lastLcm, minRoomWidth);
			lastLength = calcSize(tileSize, jointSize, lastLength, lastLcm, minRoomLength);
			if(lastWidth == -1 || lastLength == -1){
				printf("Reseni neexistuje.\n");
				return 0;
			}
			lastLcm = lcm(lastLcm, tileSize+jointSize);
		}
		
	}

	
	printf("Velikost: %.1f x %.1f\n", lastWidth/(double)10, lastLength/(double)10);
	
	return 0;
}
