#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	int PID;
	char lineGot[256];
	char *cmd;
	char *cmd2;
	char *parse;
	char *parse2;
	while (1){
		printf("cmd: ");
		fgets(lineGot, 256, stdin); // Get a string from user (includes \n)
		cmd = strtok(lineGot, "\n");
		cmd2 = strtok(cmd, " ");
		parse = strtok(NULL, " ");
		parse2 = strtok(NULL, " ");
		if( strcmp(cmd, "e") == 0 ) // loop terminates when "e" is typed
			exit (0);
		// creates a new process. Parent gets the child’s process ID. Child gets 0.
		if ( (PID=fork()) > 0)
		{
			wait(NULL);
		}
		else if (PID == 0) /* child process */
		{
			char* args[] = {cmd2, parse, parse2, NULL};
			execvp (cmd2, args);
			/* exec cannot return. If so do the following */
			fprintf (stderr, "Cannot execute %s\n", cmd);
			exit(1); /* exec failed */
		}
		else if ( PID == -1)
		{
			fprintf (stderr, "Cannot create a new process\n");
			exit (2);
		}
	}
}
