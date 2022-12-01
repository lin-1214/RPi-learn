#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

char buf[256];
char command[256];
char *echos[] = {"I think of a lot of good ideas when going to the bathroom - I guess I have a real stream of consciousness", "Tim Horton was a hockey player but is the name of a coffee chain, which means my dream of a goat sanctuary being my legacy is not unrealistic", "I started a sensory deprivation chamber business - it involves really dark curtains, ear plugs, and a sleeping mask"};

int main(){
	int fd[2]; //0: read,1: write
       	srand(time(0));	
	pipe(fd);
	printf("Please enter a command(pwd, ls, echo): ");
	scanf("%s", command);

	pid_t pid = fork();
	if (pid == 0) {
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if(strcmp(command,"ls") == 0) execlp("ls", "./", NULL);
		else if (strcmp(command, "pwd") == 0) execlp("pwd", "./", NULL);
		else if (strcmp(command, "echo") == 0) execlp ("echo", "echo", echos[rand()%3], NULL);
		else execlp("echo", "echo", "Command not found", NULL);
	}

	close(fd[1]);

	read(fd[0], buf, sizeof(buf));
	write(1, buf, sizeof(buf));
	printf("End process\n");
	return 0;
}
