//Anthony Lemmon
//CSC 4421
//Lab 6
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5 //Global variable for the thread count

struct X_VAR{ //Struct that is used to pass the value of x each time I create a thread
	int x;};

int x_a = 19530; //Original x value

void *calculate_s(void *X_VAR); //Subtraction function declaration
void *calculate_d(void *X_VAR); //Division function declaration

int main(){ //Main
	struct X_VAR x_p; //Object for passing x value
	x_p.x = x_a; //Pass 19530 to the object
	pthread_t thread_s, thread_d; //Subtraction and division threads
	int create_s, create_d; 
	int i;
	for(i=1; i<=NUM_THREADS; i++){ //Loops 5 times
		printf("ITERATION %d\n", i);
		struct X_VAR *x_p = malloc(sizeof(struct X_VAR));
		x_p->x = x_a; //Pass current value of x before subtraction
		create_s = pthread_create(&thread_s, NULL, calculate_s, x_p); //Create subtraction thread
		pthread_join(thread_s, NULL); //Wait for this thread to complete
		x_p->x = x_a; //Pass current value of x before division
		create_d = pthread_create(&thread_d, NULL, calculate_d, x_p); //Create division thread
		pthread_join(thread_d, NULL);} //Wait for this thread to complete
	return 0;}

void *calculate_s(void *X_VAR){ //Subtraction function
	struct X_VAR* x_p = (struct X_VAR*) X_VAR; //Object for x value
	x_a = x_p->x; //Pass current x value to object
	x_a -= 5; //Subtract 5 from that value
	printf("Thread 1: %d\n", x_a);} 

void *calculate_d(void *X_VAR){ //Division function
	struct X_VAR *x_p = (struct X_VAR*) X_VAR; //Object for x value
        x_a = x_p->x; //Pass current x value to object
        x_a /= 5; //Divide 5 from that value
        printf("Thread 2: %d\n", x_a);}

	
