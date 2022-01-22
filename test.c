#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
/*
int main()
{
	int fd[2];
	pipe(fd);
	int infd = dup(0);
	int outfd = dup(1);
	dup2(fd[1], 1);
	dup2(fd[0], 0);
	write(fd[1], "b", 1);
	close(fd[1]);
	close(fd[0]);

	char *str = malloc(1000);
	//int reaidr = read(0, str, 8);
	printf("pid = %i\n", getpid());
	puts("blablabla");
	dup2(infd, 0);
	pipe(fd);
	dup2(infd, 0);
	dup2(outfd, 1);
	read(fd[0], str, 8);
	printf("%s\n", str);
}*/

int main()
{
	int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC);
	dup2(fd, 1);
	write(1, "b", 1);
}	
