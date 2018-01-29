#include <cstdio>
#include <cstdlib>
#include <cstring>

int readModul(){
	int input = 0;
	int scanfRes = scanf("%d", &input);
	if(scanfRes != 1 || input < 1 || input > 10){
		printf("Nespravny vstup.\n");
		exit(1);
	}
	return input;
}

int readQuery(int* max){
	
	char type[7];
	int scanfRes = scanf("%6s", type);
			
			if(scanfRes == EOF)
				exit(1);
			
			if(scanfRes != 1 
					|| (strncmp(type, "list", 5) != 0 
					&& strncmp(type, "count", 6) != 0)){
				printf("Nespravny vstup.\n");
				exit(1);
			}
			
			if(scanf("%d", max) != 1
					|| *max < 1){
				printf("Nespravny vstup.\n");
				exit(1);
			}
			
			if(type[0] == 'c')
				return 0;
			else
				return 1;
			
}

void printArray(char* array, int max){
	printf("[");
	for(int i = 0; i < max; i++){
		printf("%c", array[i]);
	}
	printf("]\n");
}

void lots(int type, char modul, char* array, int* count, int max, int pos, char lastButOne, char last, int cCount, int cUsed, int pCount){
	
	if(pCount == modul && max-pos != 1){
		if((last != 'I' && lastButOne == 'I') || (last != 'I' && lastButOne != 'I') || (last == 'I' && lastButOne == 'I')){
			array[pos] = 'P';
			lots(type, modul, array, count, max, pos+1, last, array[pos], cCount+1, cUsed, 0);
		}
	}
	
	else if(lastButOne != 'I' && last == 'I'){
		if(pCount != modul){
			if(max-pos != 1){
				array[pos] = 'I';
				lots(type, modul, array, count, max, pos+1, last, array[pos], cCount+1, cUsed, pCount+1);
			}
			else{
				array[pos] = 'I';
				if(type)
					printArray(array, max);
				(*count)++;
			}
		}
	}
	
	else if(max-pos != 1){
		for(int i = 0; i < 4; i++){
		
			switch(i){
				case 0:
					array[pos] = 'P';
					lots(type, modul, array, count, max, pos+1, last, array[pos], cCount+1, cUsed, 0);
					break;
				case 1:
					array[pos] = 'I';
					lots(type, modul, array, count, max, pos+1, last, array[pos], cCount+1, cUsed, pCount+1);
					break;
				case 2:
					array[pos] = 'R';
					lots(type, modul, array, count, max, pos+1, last, array[pos], cCount+1, cUsed, pCount+1);
					break;
				case 3:
					if(cCount >= modul || !cUsed){
						array[pos] = 'C';
						lots(type, modul, array, count, max, pos+1, last, array[pos], 0, 1, pCount+1);
					}
					break;		
			}
		}
	}
	else{
	
		for(int i = 0; i < 4; i++){
		
			if(pCount == modul){
				array[pos] = 'P';
				if(type){
					printArray(array, max);
				}
				(*count)++;
				break;
			}
			else{
				switch(i){
					case 0:
						array[pos] = 'P';
						break;
					case 1:
						if(last == 'I'){
							array[pos] = 'I';
						}
						else
							continue;
						break;
					case 2:
						array[pos] = 'R';
						break;
					case 3:
						if(cCount >= modul || !cUsed){
							array[pos] = 'C';
						}
						else
							continue;
						break;			
				}
			}
			
			if(type){
				printArray(array, max);
			}
			(*count)++;
		}
	}
}

int main (void){

	char* array;
	int count = 0;
	
	int modul = 0;
	int type = 0;
	int max = 0;

	printf("Modul:\n");
	modul = readModul();
	
	printf("Vypocty:\n");
	
	while(1){
		count = 0;
		type = readQuery(&max);
		array = (char*)malloc(max * sizeof(*array));
		lots(type, modul, array, &count, max, 0, '0', '0', 0, 0, 0);
		printf("=> %d\n", count);
		free(array);
	}
	
	
	return 0;
}
