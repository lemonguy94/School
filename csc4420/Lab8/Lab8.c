//Anthony Lemmon (eu6623)
//CSC4421
//Lab 8
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

//Function prototypes
int readFile(); 
void writeFile(int x);
//For usage with signal
void action(int input){
	sleep(1);}

int main(){
	int pid;
	int x = 19530;
	writeFile(x); 
	printf("x = %d\n", x);
	pid = fork(); 
	if (pid == -1){ //Fork error
		perror("Error with fork");
		exit(1);}
	else if(pid > 0){ //Parent, x-=5
		sleep(1);
		for(int i = 1; i <= 5; i++){
			printf("\nITERATION %d\n", i);
			x = readFile(); 
			x -= 5;
			printf("Parent: %d\n", x);
			writeFile(x); 
			kill(pid, SIGUSR1); 
			signal(SIGUSR1, action);
			pause();}}
	else if(pid == 0){ //Child, x/=5
		for(int i = 1; i <= 5; i++){
			signal(SIGUSR1, action);
			pause();
			x = readFile();
			x /= 5;
			printf("Child: %d\n", x);
			writeFile(x);
			kill(getppid(), SIGUSR1);}}
	return 0;}

int readFile() //Read value from testfile.txt
{
	char buffer[10];		
	int fd;			
	if((fd = open("testfile.txt", O_RDONLY )) == -1){
		perror("Error opening file");
		exit(2);}
	if(read(fd, buffer, 10) == -1){
		perror("Error reading file");
		exit(3);}
	close(fd);
	return atoi(buffer);
}

void writeFile(int writeFile) //Write value to testfile.txt
{
	char buffer[10];		
	int fd;				
	int xBytes;	
	if ( (fd = open("testfile.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644 )) == -1 ){
		perror("Error opening file");
		exit(4);}
	xBytes = sprintf(buffer, "%d", writeFile);
	if ( write(fd, buffer, xBytes) == -1 )
	{
		perror("Error writing to file");
		exit(5);}
	close(fd);
	return;
}


