#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
	pid_t pid_1 = fork();

	if ( pid_1 == 0){
		execl("/bin/ls", "ls", "-l",  NULL);
	}
	int status;
	waitpid(pid_1, &status, 0);
	printf("Status: %d\n", status);
	printf("Child PID: %d, end process.\n",pid_1);
	return 0;
}
