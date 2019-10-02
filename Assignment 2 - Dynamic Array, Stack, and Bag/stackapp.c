/*	stack.c: Stack application. */
/* Name: John Olgin */
/* Date: 4/23/18 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}
/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */
    struct DynArr *array = newDynArr(10);
    char character;
    while((character = nextChar(s)) != '0'){
        switch(character){
            case '}' :
                if(topDynArr(array) == '{'){
                    popDynArr(array);
                    break;
                }
                return 0;
                
            case ']' :
                if(topDynArr(array) == '['){
                    popDynArr(array);
                    break;
                }
                return 0;
                
            case ')' :
                if(topDynArr(array) == '('){
                    popDynArr(array);
                    break;
                }
                return 0;
            case '{' :
            case '[' :
            case '(' :
                pushDynArr(array, character);
                break;
        }
    }
    
    
    if(sizeDynArr(array) != 0){
        return 0;
    }
    
    deleteDynArr(array);
    return 1;
}


int main(int argc, char* argv[]){
	
	char* s=argv[1];
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

