#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this
    struct Link *begin;
    struct Link *end;
    begin = (struct Link *)malloc(sizeof(struct Link));
    end = (struct Link *)malloc(sizeof(struct Link));
    begin->next = end;
    end->prev = begin;
    
    list->frontSentinel = begin;
    list->backSentinel = end;
    list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
    
    assert(list != 0 && link != 0);
    struct Link *new;
    new = (struct Link*)malloc(sizeof(struct Link));
    new->prev = link->prev;
    new->next = link;
    new->value = value;
    link->prev->next = new;
    link->prev = new;
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this
    assert(list != 0 && link != 0);
    link->prev->next = link->next;
    link->next->prev = link->prev;
    free(link);
    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
    assert(list != 0);
    addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
    assert(list != 0);
    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
    assert(list != 0 && !linkedListIsEmpty(list));
    return (list->frontSentinel->next->value);}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
    assert(list != 0 && !linkedListIsEmpty(list));
    return (list->backSentinel->prev->value);
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
    assert(list != 0 && !linkedListIsEmpty(list));
    removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
    assert(list != 0 && !linkedListIsEmpty(list));
    removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
    assert(list != 0);
    return (list->size == 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this
    assert(list != 0 && !linkedListIsEmpty(list));
    struct Link *temp = list->frontSentinel->next;
    assert(temp != 0);
    while(temp != list->backSentinel) {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
    linkedListAddFront(list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
    assert(list != 0 && !linkedListIsEmpty(list));
    struct Link *temp = list->frontSentinel->next;
    while(temp != list->backSentinel) {
        if (temp->value == value) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
    assert(list != 0 && !linkedListIsEmpty(list));
    struct Link *temp = list->frontSentinel->next;
    while (temp != list->backSentinel) {
        if (temp->value == value) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
            list->size--;
            break;
        }
        temp = temp->next;
    }
}
