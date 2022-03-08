#include <unistd.h>

int main(int ac, char **av, char **envp)
{
	char *args[] = {"sbalbvjv", "1s"};
	execve("/bin/sleep", args, envp);
}
