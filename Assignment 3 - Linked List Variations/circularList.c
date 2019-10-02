#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
    struct Link *newLink;
    newLink = (struct Link *) malloc( sizeof(struct Link) );
    newLink->next = newLink;
    newLink->prev = newLink;
    list->size = 0;
    list->sentinel = newLink;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this
    struct Link *newLink;
    newLink = (struct Link *) malloc( sizeof(struct Link) );
    newLink->next = NULL;
    newLink->prev = NULL;
    newLink->value = value;
    return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
    struct Link *newLink;
    newLink = createLink(value);
    newLink->prev = link;
    newLink->next = link->next;
    link->next->prev = newLink;
    link->next = newLink;
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
    struct Link *tempLink;
    tempLink = list->sentinel;
    while (tempLink->next != link) {
        tempLink = tempLink->next;
    }
    
    tempLink->next = link->next;
    list->size--;
    free(link);
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* newList = malloc(sizeof(struct CircularList));
	init(newList);
	return newList;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this
    while(!circularListIsEmpty(list)) {
        circularListRemoveFront(list);
    }
    free(list->sentinel);
    free(list);
    
    if (circularListIsEmpty(list)) {
        printf("The list is now destroyed. \n\n");
    }
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
    TYPE frontLinkValue = 0;
    if (list->sentinel != NULL) {
        frontLinkValue = list->sentinel->next->value;
    }
    return frontLinkValue;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
    TYPE backLinkValue = 0;
    if (list->sentinel != NULL) {
        backLinkValue = list->sentinel->prev->value;
    }
    return backLinkValue;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
    if (list->size > 0) {
        removeLink(list, list->sentinel->next);
    }
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
    if (!circularListIsEmpty(list)) {
        removeLink(list, list->sentinel->prev);
    }
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
    return (list->size == 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
    struct Link *linkToPrint = list->sentinel->next;
    int i = 0;
    while (i < list->size) {
        printf("%g\n", linkToPrint->value);
        linkToPrint = linkToPrint->next;
        i++;
    }
}


/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this
    struct Link *prev = NULL;
    struct Link *current = list->sentinel->next;
    struct Link *next;
    int i = 0;
    while (i < list->size) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        i++;
    }
    list->sentinel->next = prev;
}
