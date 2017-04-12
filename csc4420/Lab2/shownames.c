#include <dirent.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	struct dirent *direntp;
	DIR *var;

	if(argc != 2){
		fprintf(stderr, "Usage: %s directory name \n", argv[0]);
		return 1;}
	
	if((var=opendir(argv[1])) == NULL){
		perror("Failed to open directory");
		return 1;}
	
	while((direntp=readdir(var)) != NULL){
		printf("%s\n", direntp->d_name);}
	int close;
	while((close=closedir(var) == -1) && (errno == EINTR));
	return 0;
}

