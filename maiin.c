//#include <stdio.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
char	**ft_get_bin_path(char **env)
{
	int i;
	char *trimmed;
	char **bin_path;

	if (!env[0])
		return (NULL);
	i = 0;
	while (!ft_strnstr(env[i], "PATH", 5))
		i++;
	trimmed = ft_strtrim(env[i], "PATH=");
	bin_path = ft_split(trimmed, ':');
	return (bin_path);
}

char	*ft_get_access(char **path)
{
	int i;

	i = 0;
	while (access(path[i], X_OK) != 0 && path[i])
	{
	//	printf("path[i] = %s\n", path[i]);
//		puts("----loop------");
		i++;
	}
	return (path[i]);
}
int main(int ac, char **av, char **envp)
{
	if (!envp[0])
		return(0);
	
	char **str1 = ft_get_bin_path(envp);
	char **str2 = ft_get_bin_path(envp);
//		if (str)
//			for (int i=0; str[i]; i++)
//				printf("%s\n", str[i]);
	int i = 0;
	i = 0;
	char **argv1;

	char **argv2;
	argv1 = ft_split(av[2], ' ');
	argv2 = ft_split(av[3], ' ');
	char *cmd1 = ft_strjoin("/", argv1[0]);
	char *cmd2 = ft_strjoin("/", argv2[0]);
	while (str1[i])
	{
		str1[i] = ft_strjoin(str1[i], cmd1);
		str2[i] = ft_strjoin(str2[i], cmd2);
		i++;
	}
//	printf("%s\n", str[i]);
	int pip[2];
	pipe(pip);
	printf("pip[0] = %d\n", pip[0]);
	printf("pip[1] = %d\n", pip[1]);
	if (fork() == 0)
	{
		int fd = open(av[1], O_RDONLY);
		dup2(fd, 0);
		dup2(pip[1], 1);
		close(pip[0]);
		printf("access 1 = %s", ft_get_access(str1));
		execve(ft_get_access(str1), argv1, envp);
	}
	else
	{
		i = 0;
		int fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		printf("fd = %d\n", fd);
		dup2(fd, 1);
		dup2(pip[0], 0);
		execve(ft_get_access(str2), argv2, envp);
	}
	printf("ERROR\n");
}
