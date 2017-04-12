//Anthony Lemmon
//CSC 4421
//Lab 7
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	int x = 19530; 
	size_t X_SIZE = sizeof(x);
	printf("X = %d\n\n", x);
        int parentpipefd[2];
	int childpipefd[2]; 
        pid_t cpid;
        if (pipe(parentpipefd) == -1 || pipe(childpipefd) == -1) { //Parent and child pipes
                perror("pipe");
                exit(EXIT_FAILURE);}
	if (write(parentpipefd[1], &x, X_SIZE) == -1){ //Initialize write to parent pipe
		printf("Parent write failed.\n");}
        cpid = fork();
        if (cpid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);}
        else if (cpid == 0) { //Child process
		for(int i = 1; i <= 5; i++){         
                	if (read(parentpipefd[0], &x, X_SIZE) == -1){ //Read x value from parent pipe
				printf("Child read failed.\n");
				return 1;}
			x -= 5;
			printf("ITERATION %d:\n", i);
			printf("Child: x = %d\n", x);
                	write(childpipefd[1], &x, X_SIZE);}} //Write x value for parent piping
	else { //Parent process
		for(int i = 1; i <= 5; i++){
                	if (read(childpipefd[0], &x, X_SIZE) == -1){ //Read x value from child pipe
				printf("Parent read failed.\n");
				return 1;}
                        x /= 5;
                        printf("Parent: x = %d\n", x);
                        write(parentpipefd[1], &x, X_SIZE); //Write x value for child piping
                	write(STDOUT_FILENO, "\n", 1);}}
	return 0;}

