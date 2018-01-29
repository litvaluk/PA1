#include <cstdio>
#include <cstdlib>

struct charArray{
	char* array;
	int size;
	int n;	
};

/*--------------------
Reads and formats the text inputted by the user
to an array given in the parameter.
----------------------
First parameter is a pointer to the array.
----------------------*/
void readText(charArray* text){
	
	char current = 0;
	char last = 0;
	int prevIsSpace = 0;
	int prevIsSymbol = 0;
	text->n = 0;
	
	text->array = (char*)malloc(sizeof(*(text->array)) * text->size);
	
	while(1){
		
		if(text->n == text->size){
			text->array = (char*)realloc(text->array, sizeof(*(text->array)) * text->size * 1.5);
			text->size *= 1.5;
		}
		
		int scanfRes = scanf("%c", &current);
		
		if(scanfRes == EOF){
			printf("Nespravny vstup.\n");
			free(text->array);
			exit(1);
		}
		
		if(last == 10 && current == 10 && !prevIsSymbol){
			text->array[text->n] = (char)32;
			break;
		}
		
		if((current >= 65 && current <= 90) || (current >= 97 && current <= 122)){
			prevIsSymbol = 0;
			last = current;
			if(current >= 65 && current <= 90)
				text->array[text->n] = current+32;
			else
				text->array[text->n] = current;	
			(text->n)++;
			prevIsSpace = 0;
		}
		else if(!prevIsSpace && current == 32 && ((last >= 65 && last <= 90) || (last >= 97 && last <= 122))){
			prevIsSymbol = 0;
			text->array[text->n] = current;	
			(text->n)++;
			prevIsSpace = 1;
		}
		else if(current == 10){
			prevIsSymbol = 0;
			last = current;
			text->array[text->n] = '\n';	
			(text->n)++;
		}
		else{
			if((last >= 65 && last <= 90) || (last >= 97 && last <= 122)){
				text->array[text->n] = ' ';
				(text->n)++;
				prevIsSpace = 1;
				last = ' ';
			}
			else
				prevIsSymbol = 1;
		}
		
		
	}
}

/*--------------------
Reads and formats the text to be searched inputted by the user
to an array given in the parameter. If it is EOF, then the loop ends.
----------------------
First parameter is a pointer to the array.
Second parameter is pointer to an integer which
indicates if it is EOF or not.
----------------------*/
void readSearchText(charArray* textToSearch, int* isEof){
	
	char current = 0;
	char last = 0;
	int prevIsSpace = 0;
	textToSearch->n = 0;
	
	textToSearch->array = (char*)malloc(sizeof(*(textToSearch->array)) * textToSearch->size);
	
	while(1){
		
		if(textToSearch->n == textToSearch->size){
			textToSearch->array = (char*)realloc(textToSearch->array, sizeof(*(textToSearch->array)) * textToSearch->size * 1.5);
			textToSearch->size *= 1.5;
		}
		
		int scanfRes = scanf("%c", &current);
		
		if(scanfRes == EOF){
			*isEof = 1;
			break;
		}
		
		if((current >= 65 && current <= 90) || (current >= 97 && current <= 122)){
			last = current;
			if(current >= 65 && current <= 90)
				textToSearch->array[textToSearch->n] = current+32;
			else
				textToSearch->array[textToSearch->n] = current;		
			(textToSearch->n)++;
			prevIsSpace = 0;
		}
		else if(!prevIsSpace && current == 32 && ((last >= 65 && last <= 90) || (last >= 97 && last <= 122))){
			textToSearch->array[textToSearch->n] = current;	
			(textToSearch->n)++;
			prevIsSpace = 1;
		}
		else if(current == 10){
			break;
		}
		
	}
}

/*--------------------
Prints certain text if the text is found or not.
Returns number of occurances.
----------------------
First parameter is a pointer to the array in which
the text will be searched.
Second parameter is the pointer to array, which
holds the text to be searched.
----------------------*/
int printSearch(charArray* text, charArray* textToSearch){
	
	int count = 0;
	int line = 1;
	
	for(int i = 0; i<text->n; i++){
		
			int tmp = i;
			
			if(text->array[i] == 10){
				line++;
			}
			
			if(i == 0 || (i > 0 && ((text->array[i-1] == 32) || (text->array[i-1] == 10)))){
				for(int j = 0; j<textToSearch->n; j++){
				
					if(tmp == text->n){
						printf("Nenalezeno\n");
						return 0;
					}
					
					if(text->array[tmp] == 10 && text->array[tmp+1] == 10){
						tmp++;
						j--;
						continue;
					}
					if(text->array[tmp] == 10 && textToSearch->array[j] == 32){
						tmp++;
						continue;
					}
					else if(text->array[tmp] == 32 && text->array[tmp+1] == 10 && textToSearch->array[j] == 32){
						tmp += 2;
						continue;
					}
					else if(text->array[tmp] != textToSearch->array[j]){
						break;	
					}
					
					if(j == textToSearch->n-1 && (text->array[tmp+1] == 32 || text->array[tmp+1] == 10)){
						if(count == 0)
							printf("Nalezeno: %d", line);
						else
							printf(", %d", line);
						count++;
					}
					tmp++;
				}
			}

	}
	
	if(count == 0)
		printf("Nenalezeno\n");
	else
		printf("\n");
	
	return count;
}

/*--------------------
Asks user to input text and then searches through
the text to find occurances and prints the lines, where
the occurance was found.
----------------------
First parameter is a pointer to the array in which
the text will be searched.
Second parameter is the pointer to array, which
holds the text to be searched.
----------------------*/
void search(charArray* text, charArray* textToSearch){
	int isEof = 0;
	printf("Hledani:\n");
	
	while(1){
		readSearchText(textToSearch, &isEof);
	
		if(textToSearch->n == 0 && isEof == 1){
			free(textToSearch->array);
			free(text->array);
			exit(1);
		}
		
		if(isEof == 1){
			printSearch(text, textToSearch);
			free(textToSearch->array);
			break;
		}
		
		if(textToSearch->n == 0){
			printf("Neplatny dotaz\n");
			free(textToSearch->array);
			continue;
		}
		
		printSearch(text, textToSearch);
		free(textToSearch->array);
	}
}

int main(void){
	
	charArray text;
	charArray textToSearch;
	text.size = 20;
	textToSearch.size = 10;
	
	printf("Text:\n");
	readText(&text);

	/////////////////////////////// zobraz
	/*for(int i = 0; i<text.n; i++){
		printf("%c", text.array[i]);
	}
	printf("\n");*/
	///////////////////////////////
	
	search(&text, &textToSearch);
	
	free(text.array);
	return 0;
}
