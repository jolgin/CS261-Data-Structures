#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
    char *word = nextWord(file);
    
    while(word) {
        hashMapPut(map, word, 1);
        free(word);
        word=nextWord(file);
    }
    
    hashMapPrint(map);
    free(word);
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    printf("oh no");
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("/Users/johnolgin/Downloads/Programming_Assignment5_skeleton_files_S18/dictionary.txt", "r");
    assert(file != NULL);
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        int validWord = 0;
        
        
        while(validWord == 0){
            for(int i = 0; i < strlen(inputBuffer); i++) {
                if((inputBuffer[i] >= 97 && inputBuffer[i] <= 122) || (inputBuffer[i] <= 90 && inputBuffer[i] >= 65)) {
                }
                else {
                    printf("Invalid word, please enter only letters: \n");
                    scanf("%s", inputBuffer);
                    i = 0;
                }
            }
            
            validWord = 1;
        }
        
        /*for(int i = 0; strlen(inputBuffer); i++){
            inputBuffer[i] = tolower(inputBuffer[i]);
        }*/
        
        // Implement the spell checker code here..
        
        if(!hashMapContainsKey(map, inputBuffer)) {
            printf("The inputted word %s is spelled incorrectly. \n", inputBuffer);
        }
        else {
            printf("The inputted word %s is spelled correctly. \n", inputBuffer);
        }
        
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}
