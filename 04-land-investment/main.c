#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_SIZE 2000

/*
Reads the size of the array from the user.
------------------------------------------------
First parameter is a pointer to width variable.
Second parameter is a pointer to height variable.
*/
void readMapSize(int* w, int* h){
	if(scanf("%d %d", h, w) != 2
				|| *w <= 0
				|| *h <= 0
				|| *w > MAX_SIZE
				|| *h > MAX_SIZE){
		printf("Nespravny vstup.\n");
		exit(1);
	}
}

/*
Reads the map and sets each element's price.
------------------------------------------------
First parameter is a 2D array.
Second parameter is width.
Third parameter is height.
*/
void readAndSetMap(int (*map)[MAX_SIZE], int w, int h){
	int price = 0;
	int count = 0;
	int i = 0;
	int j = 0;
	
	while(1){
		if(count == w*h){
			break;
		}
		int scanfRes = scanf("%d", &price);
		if((scanfRes == EOF && count != w*h)
				|| scanfRes != 1
				|| price <= 0){
			printf("Nespravny vstup.\n");
			exit(1);
		}
		if(j > h-1){
			i++;
			j=0;
		}
		map[i][j] = price;
		j++;
		count++;
	}
}

/*
Returns maximum area that can be bought for the
given amount of investment and the number of ways.
------------------------------------------------
First parameter is a 2D array.
Second parameter is the width of the array.
Third parameter is the height of the array.
Fourth parameter is the amount of investment.
Fifth parameter is the pointer to the ways variable.
*/
int countMaxArea(int (*map)[MAX_SIZE], int w, int h, int investment, int* ways){
	
	int l = 0;
	int r = 0;
	int mapCtr = 0;
	int sizeL = 0;
	int outerSize = 0;
	static int innerMap[2000];
	
	int maxArea = 0;
	int cntr = 0;
	
	int ll = 0;
	int rr = 0;
	
	int sizeLl = 0;
	int sizeIn = 0;
	int sum = 0;
	
	for(l=0; l<h; l++){
		sizeL = 1;
		for(r=0; l+r<h; r++){
			outerSize = sizeL+r;
			if(r == 0){
				for(mapCtr=0; mapCtr<w; mapCtr++){
					innerMap[mapCtr] = map[mapCtr][l];
					
				}
			}
			else if(r != 0){
				for(mapCtr=0; mapCtr<w; mapCtr++){
					innerMap[mapCtr] += map[mapCtr][r+l];
				}
			}
			
			for(ll=0; ll<w; ll++){
				(sizeLl = 1);
				sum = innerMap[ll];
				for(rr=0; ll+rr<w; rr++){
					sizeIn = sizeLl + rr;
					if(rr != 0)
						sum += innerMap[ll+rr];
					if(sum <= investment){
						if(sizeIn*outerSize > maxArea){
							maxArea = sizeIn*outerSize;
							cntr = 1;
						}
						else if(sizeIn*outerSize == maxArea){
							cntr++;
						}
					
					}
				}
			}
			
		}
	}
	*ways = cntr;
	
	return maxArea;
}

/*
Performs the count operation.
------------------------------------------------
First parameter is the amount of investment.
Second parameter is a 2D array.
Third parameter is the width of the array.
Fourth parameter is the height of the array.
*/
void count(int investment, int (*map)[MAX_SIZE], int w, int h){
	int ways = 0;
	int area = 0;
	
	area = countMaxArea(map, w, h, investment, &ways);
	if(area == 0)
		printf("Nenalezeno.\n");
	else
		printf("Max. rozloha: %d (x %d)\n", area, ways);
}


/*
Performs the list operation.
------------------------------------------------
First parameter is the amount of investment.
Second parameter is a 2D array.
Third parameter is the width of the array.
Fourth parameter is the height of the array.
*/

void list(int investment, int (*map)[MAX_SIZE], int w, int h){
	int ways = 0;
	int area = countMaxArea(map, w, h, investment, &ways);
	if(area == 0)
		printf("Nenalezeno.\n");
	else{
		printf("Max. rozloha: %d (x %d)\n", area, ways);
		
		int l = 0;
		int r = 0;
		int mapCtr = 0;
		int sizeL = 0;
		int outerSize = 0;
		static int innerMap[2000];
		
		int ll = 0;
		int rr = 0;
		
		int sizeLl = 0;
		int sizeIn = 0;
		int sum = 0;
		
		for(l=0; l<h; l++){
			sizeL = 1;
			for(r=0; l+r<h; r++){
				outerSize = sizeL+r;
				if(r == 0){
					for(mapCtr=0; mapCtr<w; mapCtr++){
						innerMap[mapCtr] = map[mapCtr][l];
						
					}
				}
				else if(r != 0){
					for(mapCtr=0; mapCtr<w; mapCtr++){
						innerMap[mapCtr] += map[mapCtr][r+l];
					}
				}
				
				for(ll=0; ll<w; ll++){
					(sizeLl = 1);
					sum = innerMap[ll];
					for(rr=0; ll+rr<w; rr++){
						sizeIn = sizeLl + rr;
						if(rr != 0)
							sum += innerMap[ll+rr];
						if(sum <= investment){
							
							if(sizeIn*outerSize == area){
							
							printf("%d: %d x %d @ (%d,%d)\n", sum, area/sizeIn, sizeIn, l, ll);
							
							}
						
						}
					}
				}
			
			}
		}
	}	
}


/*
Reads and answers the query entered by user.
------------------------------------------------
First parameter is a 2D array.
Second parameter is width.
Third parameter is height.
*/
void query(int (*map)[MAX_SIZE], int w, int h){
		char typeOfQuery[7];
		const char* listString = "list";
		const char* countString = "count";
		
		int investment = 0;
		
		while(1){
		
			int scanfRes = scanf("%6s", typeOfQuery);
			
			if(scanfRes == EOF)
				exit(1);
			
			if(scanfRes != 1 
					|| (strncmp(typeOfQuery, listString, 5) != 0 
					&& strncmp(typeOfQuery, countString, 6) != 0)){
				printf("Nespravny vstup.\n");
				exit(1);
			}
			
			if(scanf("%d", &investment) != 1
					|| investment <= 0){
				printf("Nespravny vstup.\n");
				exit(1);
			}
			
			if(strncmp(typeOfQuery, listString, 4) == 0){
				list(investment, map, w, h);
			}
				
			if(strncmp(typeOfQuery, countString, 5) == 0)
				count(investment, map, w, h);
		}	
}

int main (void){
	
	static int map[MAX_SIZE][MAX_SIZE];
	
	int w = 0;
	int h = 0;
	
	printf("Velikost mapy:\n");
	readMapSize(&w, &h);

	printf("Cenova mapa:\n");
	readAndSetMap(map, w, h);
	
	printf("Dotazy:\n");
	query(map, w, h);
	
	return 0;
}
