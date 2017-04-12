#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	struct stat inst;
	int var;
	if((var=stat(argv[1], &inst)) == -1){
		perror("Error: Failed to open directory");
		return 1;}
	printf("%s last accessed at %s", argv[1], ctime(&inst.st_atime));}
