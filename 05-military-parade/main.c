#include <cstdio>
#include <cstdlib>
#include <cmath>

/*--------------------
Returns greatest common divisor of two numbers
using Euclidean algorithm.
----------------------
The parameters are the two numbers for calculating
the greatest common divisor of those numbers. 
----------------------*/
unsigned long long int gcd(unsigned long long int x, unsigned long long int y){
  unsigned long long int tmp;
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
unsigned long long int lcm(unsigned long long int x, unsigned long long int y){
	return x / gcd(x, y) * y;
}

/*--------------------
Frees the memory of given array, 
prints "Nespravny vstup." and exits program.
----------------------
The only parameter is a pointer to the array. 
----------------------*/
void freeExit(int* array){
	printf("Nespravny vstup.\n");
	free(array);
	exit(1);
}

/*--------------------
Handles the scanf when the value is EOF.
----------------------
First parameter is a pointer to array.
Second parameter is the value of scanf function.
Third parameter is the last char scanned by the scanf function.
Fourt parameter is the number of cycle.
----------------------*/
int eofHandle(int* array, int scanfRes, char symbol, int n){
	if(scanfRes == EOF && symbol != '}'){
			freeExit(array);
			return -1;
	}
	else if(symbol == '}' && n != 0){
		return 1;
	}
	else{
		return 0;
	}
}

/*--------------------
Handles the input of the user and returns dynamically
allocated array.
----------------------
First parameter is a pointer to variable which holds
the length of the array.
----------------------*/
int* loadArray(int* len){
	
	int n = 0;
	int* array;
	int size = 5;
	
	int scanfRes;
	char charTmp = '0';
	int intTmp;
	
	array = (int*)malloc(size * sizeof(*array));
	
	while(1){
		if(n == 0){
			scanfRes = scanf(" %c", &charTmp);
			if(eofHandle(array, scanfRes, charTmp, n)){
				break;
			}
			if(scanfRes != 1 || charTmp != '{'){
				freeExit(array);
			}
		}
		else if(n > 0 && n%2 == 1){
			scanfRes = scanf("%d", &intTmp);
			if(eofHandle(array, scanfRes, charTmp, n))
				break;
			if(scanfRes != 1 || intTmp <= 0){
				freeExit(array);
			}
			(*len)++;
			if((*len) == size){
				array = (int*)realloc(array, size * sizeof(*array) * 1.5);
				size *= 1.5;
			}
			array[(*len)-1] = intTmp;
		}
		else if(n > 0 && n%2 == 0){
			scanfRes = scanf(" %c", &charTmp);
			if(eofHandle(array, scanfRes, charTmp, n)){
				break;
			}
			if(scanfRes != 1 || charTmp != ','){
				freeExit(array);
			}
		}
		n++;
	}
	return array;
}

/*--------------------
Handles routes input and prints the lowest 
number of vehicles needed.
----------------------
First parameter is an array.
Second parameter is length of the array.
----------------------*/
void handleRoutes(int* array, int len){
	

	int from = 0;
	int to = 0;
	int scanfRes;
	long long unsigned int vehicles;
	
	while(1){
		vehicles = 0;
		scanfRes = scanf("%d %d", &from, &to);
		if(scanfRes == EOF)
			break;
		if(scanfRes != 2 || from >= to || to > len || from < 0 || to < 0){
			printf("Nespravny vstup.\n");
			break;
		}
		
		vehicles = array[to-1];
		for(int i = to-2; i >= from; i--){
			vehicles = lcm(vehicles, array[i]);
		}
		printf("Vozidel: %llu\n", vehicles);
	}
}

int main (void){
	
	int* array;
	int len = 0;
	
	printf("Pocty pruhu:\n");
	array = loadArray(&len);
	
	printf("Trasy:\n");
	handleRoutes(array, len);
		
	free(array);
	return 0;
}
