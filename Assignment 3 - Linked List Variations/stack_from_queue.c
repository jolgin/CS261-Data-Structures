/*
 * This is the file in which you'll write the functions required to 
implement a stack using two queues.  Make sure to add your name and
@oregonstate.edu
 * email address below:
 *
 * Name: John Olgin
 * Email: olginj@oregonstate.edu
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef TYPE
#define TYPE int
#endif

/**************************************************
 All of the initial Queue functions
 ***************************************************/
struct link {
	TYPE value;
	struct link * next;
};

struct listQueue {
	struct link *firstLink;
	struct link *lastLink;
	int size;
};

/*
* This function takes a queue and allocates the memory. It then
* creates a sentinel and assigns the first link and last link
* to the sentinel.
*/
void listQueueInit(struct listQueue *q) {
	
    // FIXME: you must write this
    struct link *newLink = (struct link *) malloc(sizeof(struct link));
    assert(newLink != 0);
    newLink->next = 0;
    q->firstLink = q->lastLink = newLink;
}

/*
 * This function creates a new queue. Parts of the create include 
allocating
 * the memory, initializing all of the values and returning a pointer to 
the newly
 * created queue.
 */
struct listQueue * listQueueCreate()
{
     //FIXME: you must write this
    struct listQueue *node = (struct listQueue *)malloc(sizeof(struct listQueue));
    node->firstLink = node->lastLink = NULL;
    return node;
}


/*
* This function returns a 1 or 0 based on the statement looking at
* the first link. If the next value is null it is empty, and will return 1
*/
int listQueueIsEmpty(struct listQueue *q) {
    //FIXME: you must write this
    return (q->firstLink == q->lastLink);
}

/*
 * This function adds a new link and value to the back of the queue. It 
takes
 * a list and a type variable, allocates the memory and adjusts the proper 
links
 * to make the connection. No return value.
 */
void listQueueAddBack(struct listQueue *q, TYPE e) {
    // FIXME: you must write this
    struct link *newLink = (struct link *) malloc(sizeof(struct link));
    assert(newLink != 0);
    newLink->value = e;
    newLink->next = 0;
    q->lastLink->next = newLink;
    q->lastLink = newLink;
}

/*
 * This function takes a list argument and removes the link at the front.
 */
void listQueueRemoveFront(struct listQueue *q) {
    // FIXME: you must write this
    struct link * temp = q->firstLink->next ;
    assert(!listQueueIsEmpty(q));
    if (q->firstLink->next->next == 0)
    {
        q->lastLink = q->firstLink;
    }
    q->firstLink->next = temp->next;
    
    free(temp);
}

/*
 * Function returns the value at the front of the list.
 */
TYPE listQueueFront(struct listQueue *q) {
    assert(!listQueueIsEmpty(q));
    return q->firstLink->next->value;
}


/*
* This function is a tester function that iterates through the list
* and prints out the values at each link.
*/
void printList(struct listQueue* l)
{
	assert(l != 0);
	struct link * linkToPrint = l->firstLink->next;
	while (linkToPrint != NULL)
	{
		printf("Value: %d\n", linkToPrint->value);
		linkToPrint = linkToPrint->next;
	}
}

/**************************************************
Stack Implementation
***************************************************/

struct linkedListStack {
	struct listQueue *Q1;
	struct listQueue *Q2;
	int structSize;
};

/*
 * This function initializes the values of the created Stack. Initializes 
both 
 * queues and the structSize.
 */
void linkedListStackInit(struct linkedListStack * s) {
	// FIXME: you must write this
    s->structSize = 0;
    s->Q1 = (struct listQueue*)malloc(sizeof(struct listQueue));
    s->Q2 = (struct listQueue*)malloc(sizeof(struct listQueue));
    listQueueInit(s->Q1);
    listQueueInit(s->Q2);
}

/*
* This function creates the linked list stack. It allocates the memory and 
calls the
* initialization function to initialize all of the values. It then returns 
the stack.
*/
struct linkedListStack * linkedListStackCreate(){
    // FIXME: you must write this
    struct linkedListStack* link = malloc(sizeof(struct linkedListStack));
    linkedListStackInit(link);
    return link;
}

/*
* This function returns 1 if the linked list stack is empty and otherwise 
returns a 0.
*/
int linkedListStackIsEmpty(struct linkedListStack *s) {

	// FIXME: you must write this
    if (s->structSize == 0)
    {
        return 1;
    }
    return 0;
}

/*
 * This is the linked list acting as a stack push function. It takes 
 * a linked list stack argument and a value and pushes it onto the stack. 
The
 * funciton then also increases the size of the stack by 1. 
 */
void linkedListStackPush(struct linkedListStack *s, TYPE d) {
	
    // FIXME: you must write this
    s->structSize++;
    listQueueAddBack(s->Q2, d);
    while (!listQueueIsEmpty(s->Q1))
    {
        listQueueAddBack(s->Q2, listQueueFront(s->Q1));
        listQueueRemoveFront(s->Q1);
    }
    struct listQueue* q = s->Q1;
    s->Q1 = s->Q2;
    s->Q2 = q;

}
/*
 * This funciton pops a value off of the stack. It does this by moving all 
values
 * that are currently on the stack to the other queue. The stack top is 
maintained
 * at the back of the queue list. 
 */
void linkedListStackPop(struct linkedListStack *s) {
	
    // FIXME: you must write this
    if(!listQueueIsEmpty(s->Q1)) {
        listQueueRemoveFront(s->Q1);
        s->structSize--;
    }
    
    else {
        printf("Error: The list is already empty \n\n");
    }
}
/*
 * This function returns the value that is at the back of the queue that 
is 
 * maintaing the values of the stack. 
 */
TYPE linkedListStackTop(struct linkedListStack *s) {

    // FIXME: you must write this
    assert(!listQueueIsEmpty(s->Q1));
    return listQueueFront(s->Q1);
}

/*
 * This function gores through the stack and removes each link in the 
queue.
 * It then frees the struct itself. 
 */
void linkedListStackFree(struct linkedListStack *s){
	
      assert(s != 0);
	
	while (s->structSize != 0) 
	{
		linkedListStackPop(s);
	}

	free(s->Q1->firstLink);
	free(s->Q2->firstLink);
	free(s->Q1);
	free(s->Q2);

	free(s);



}

/*
 * Main is used to test the stack ADT.
 */
int main(int argc, char* argv[])
{
	struct linkedListStack *stack = linkedListStackCreate();

	//Test Stack
	//Push 4 values onto the stack
	printf("Pushing the value: 1\n");
	linkedListStackPush(stack, 1);
	printf("Pushed.\n\n");

	printf("Pushing the value: 2\n");
	linkedListStackPush(stack, 2);
	printf("Pushed.\n\n");

	printf("Pushing the value: 3\n");
	linkedListStackPush(stack, 3);
	printf("Pushed.\n\n");

	printf("Pushing the value: 4\n");
	linkedListStackPush(stack, 4);
	printf("Pushed.\n\n");



	//Print value at the top and then remove it
	printf("Value at the top of stack %d now being popped. \n",linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));  
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	//Try to pop when the stack is empty prints error:
	printf("Trying to pop empty stack:\n");

	linkedListStackPop(stack);

	
	//Push and Pop alternating
	printf("Pushing the value: 10\n");
	linkedListStackPush(stack, 10);
	printf("Pushed.\n\n");

	printf("Pushing the value: 11\n");
	linkedListStackPush(stack, 11);
	printf("Pushed.\n\n");

	printf("One more pop:\n");
	linkedListStackPop(stack);
	printf("Value at the top of stack: %d\n", 
linkedListStackTop(stack));

	linkedListStackFree(stack);

	return 0;

}


