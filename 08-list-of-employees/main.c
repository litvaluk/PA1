#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TEmployee
{
  struct TEmployee         * m_Next;
  struct TEmployee         * m_Bak;
  char                     * m_Name;
} TEMPLOYEE;

#endif /* __PROGTEST__ */

/*--------------------
Adds a new employee to the list.
----------------------
First parameter is name (string) of the employee.
Second parameter is a pointer to the first element of the list.
----------------------*/
TEMPLOYEE* newEmployee(const char* name, TEMPLOYEE* next){
 	
 	TEMPLOYEE* tmp = (TEMPLOYEE*)malloc(sizeof(*tmp));
	int len = strlen(name);
	
	if(!next)
		tmp->m_Next = NULL;
	else
		tmp->m_Next = next;
	
	tmp->m_Bak = NULL;
	tmp->m_Name = (char*)malloc(len+1);
	strncpy(tmp->m_Name, name, len+1);
	
	return tmp;
}

/*--------------------
Clones an existing list.
If the list is empty (NULL), returns different
NULL pointer (TEMPLOYEE*).
(not the pointer pointing to src)
----------------------
First parameter is a pointer to the first element
of the original list. 
----------------------*/
TEMPLOYEE* cloneList(TEMPLOYEE* src){
	
	if(src == NULL){
		TEMPLOYEE* tmp = NULL;
		return tmp;
	}
	
	//  creating an array that will store the pointers to the elements
	//  of the original list to be able to restore at the end
	int size = 10;
	TEMPLOYEE** array = (TEMPLOYEE**)malloc(size*sizeof(**array));
	
	//  creating temporary variable storing the pointer
	//  to the first element of the original list
	TEMPLOYEE* srcStart = src;
	TEMPLOYEE* srcNext = NULL;
	
	//  allocating the first element of the cloned list
	TEMPLOYEE* tmp = (TEMPLOYEE*)malloc(sizeof(*tmp));
	
	//  creating temporary variables, one storing pointer
	//	 to the first element of the cloned list and one
	//  pointer which will point to the previous element (currently NULL)
	TEMPLOYEE* tmpStart = tmp;
	TEMPLOYEE* tmpPrev = NULL;
	
	int len;
	int i = 0;
	
	while(1){
		
		//  reallocating the size of the array if i == size
		if(i == size){
			size *= 1.5;
			array = (TEMPLOYEE**)realloc(array, size*sizeof(**array));
		}
		
		srcNext = src->m_Next;
		
		//  adding next element of the original list to array
		array[i] = srcNext;
		
		if(tmpPrev)
			tmpPrev->m_Next = tmp;
		
		//  --IMPORTANT--
		//  reorganizing pointers of each element in both lists
		//  for effective cloning
		src->m_Next = tmp;
		tmp->m_Bak = src;	
		tmp->m_Next = NULL;
		
		//  assigning name
		len = strlen(src->m_Name);
		tmp->m_Name = (char*)malloc(len+1);
		strncpy(tmp->m_Name, src->m_Name, len+1);

		//  ending the loop if the next element doesn't exist
		if(srcNext == NULL)
			break;
		
		//  storing current element of the clone to a variable
		//  and allocating new memory for a new one
		tmpPrev = tmp;
		tmp = (TEMPLOYEE*)malloc(sizeof(*tmp));
		
		src = srcNext;

		i++;
	}
	
	//  setting temporary variables so they point
	//  to the starting elements
	src = srcStart;
	tmp = tmpStart;

	//  --MAGIC--
	//	 using reorganized lists to assign the right
	//  representative in the cloned list
	while(tmp){
	
		if(tmp->m_Bak->m_Bak == NULL)
			tmp->m_Bak = NULL;
			
		else
			tmp->m_Bak = tmp->m_Bak->m_Bak->m_Next;
			
		tmp = tmp->m_Next;
	}
	//  --END OF MAGIC--
	
	//  setting the temporary variables so they point
	//  to the starting elements again
	src = srcStart;
	tmp = tmpStart;
	
	//  restoring the original list
	for(int j = 0; j <= i; j++){
		src->m_Next = array[j];
		src = src->m_Next;
	}
	
	free(array);
	return tmpStart;
	
}

/*--------------------
Frees an existing list.
----------------------
First parameter is a pointer to the first element of the list
to be freed.
----------------------*/
void freeList(TEMPLOYEE* src){
	
	TEMPLOYEE* tmp = src;

	while(src){
	
		tmp = src->m_Next;
		free(src->m_Name);
		free(src);
		src = tmp;
		
	}
}

#ifndef __PROGTEST__
int                main         ( int               argc, 
                                  char            * argv [] )
{
  TEMPLOYEE * a, *b;
  char tmp[100];

  assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
  a = NULL;
  a = newEmployee ( "Peter", a );
  a = newEmployee ( "John", a );
  a = newEmployee ( "Joe", a );
  a = newEmployee ( "Maria", a );
  a -> m_Bak = a -> m_Next;
  a -> m_Next -> m_Next -> m_Bak = a -> m_Next -> m_Next -> m_Next;
  a -> m_Next -> m_Next -> m_Next -> m_Bak = a -> m_Next;
  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Bak == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  b = cloneList ( a );
  strncpy ( tmp, "Moe", sizeof ( tmp ) );
  a = newEmployee ( tmp, a );
  strncpy ( tmp, "Victoria", sizeof ( tmp ) );
  a = newEmployee ( tmp, a );
  strncpy ( tmp, "Peter", sizeof ( tmp ) );
  a = newEmployee ( tmp, a );
  b -> m_Next -> m_Next -> m_Next -> m_Bak = b -> m_Next -> m_Next;
  assert ( a
           && ! strcmp ( a -> m_Name, "Peter" )
           && a -> m_Bak == NULL );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Victoria" )
           && a -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "Moe" )
           && a -> m_Next -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
           && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Bak == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Bak == NULL );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( a );
  b -> m_Next -> m_Bak = b -> m_Next;
  a = cloneList ( b );
  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Bak == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Bak == a -> m_Next );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Bak == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Bak == b -> m_Next );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( b );
  freeList ( a );
  return 0;
}
#endif /* __PROGTEST__ */
