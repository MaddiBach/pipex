/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 00:28:45 by maddi             #+#    #+#             */
/*   Updated: 2022/06/29 17:19:38 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_handle_error(char *error) // a refaire
{
	int pid;
	pid = fork();
	if (!pid)
		exit(EXIT_FAILURE);
	perror(error);
}

int ft_exec_cmd0(char **av, char **envp, int *pip)
{
	pid_t pid;
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = ft_split(av[2], ' '); // 1
	printf("exec_cmd0\n");
	cmd->binpath = ft_get_bin_path(envp, cmd->args); // 2
	pid = fork();
	if (pid < 0)
		ft_handle_error("fork");
	if (!pid)
	{
		dup2(pip[WRITE], 1);
		close(pip[READ]);
		close(pip[WRITE]);
		int execret = execve(cmd->binpath, cmd->args, envp);
		if (execret < 0)
			perror("process 1");
	}
	ft_delcmd(cmd);
	return (pid);
}

int ft_exec_cmd1(char **av, char **envp, int *pip)
{
	int pid;
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));					 // code dupliquer avec cmd0
	cmd->args = ft_split(av[3], ' ');				 // same
	cmd->binpath = ft_get_bin_path(envp, cmd->args); // same
	pid = fork();									 // same
	if (pid < 0)									 // same
		perror("fork");								 // same
	if (!pid)
	{
		dup2(pip[READ], STDIN_FILENO);
		close(pip[READ]);
		close(pip[WRITE]);
		int execret = execve(cmd->binpath, cmd->args, envp);
		if (execret < 0)
			perror("process 2");
	}
	ft_delcmd(cmd);
	return (pid);
}

int ft_open(char **av)
{
	int infile;
	int outfile;
	int dupret;

	infile = open(av[1], O_RDONLY); // utiliser access
	if (infile < 0)
		return (ft_handle_error("infile")); // arf
	outfile = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (outfile < 0)
		return (ft_handle_error("outfile"));
	dupret = dup2(infile, STDIN_FILENO);
	if (dupret < 0)
		return (ft_handle_error("dup2 infile"));
	dupret = dup2(outfile, STDOUT_FILENO);
	if (dupret < 0)
		return (ft_handle_error("dup2 outfile"));
	close(outfile);
	close(infile);
	return (1);
}

int main(int ac, char **av, char **envp)
{
	int openret;
	int pip[2];
	int status;
	if (ac != 5)
	{
		ft_putstr_fd("Invalid Number of Arguments", STDERR_FILENO);
		return (1);
	}
	if (*envp == NULL)
	{
		ft_putstr_fd("NULL env : Fail", STDERR_FILENO);
		return (2);
	}
	pipe(pip); // erreur non handle
	openret = ft_open(av);
	if (openret == 0)
		return (1);
	int pid1 = ft_exec_cmd0(av, envp, pip);
	int pid2 = ft_exec_cmd1(av, envp, pip);
	close(pip[READ]);
	close(pip[WRITE]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
