#include <stdio.h> 
#include <unistd.h> 
int main (void) 
{ 
	printf("I am process %ld\n", (long) getpid()); 
	printf("My parent is %ld\n", (long)getppid()); 
	printf("Process user id is %ld\n", (long)getuid()); 
	printf("Group id is %ld\n", (long)getgid()); return 0;
}
