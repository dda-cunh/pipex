/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/05/03 01:53:30 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	parent(int pipefd[2], int tmp, int l)
{
	int	status;

	close_fds((int []){pipefd[1], tmp}, 2);
	waitpid(l, &status, 0);
	if (status != 2)
	{
		tmp = open("tmp", O_WRONLY | O_TRUNC);
		if (tmp == -1)
			return (2);
		read_write(pipefd[0], tmp);
		close(tmp);
	}
	return (WEXITSTATUS(status));
}

static int	child(char **cmd, char **envp)
{
	int		l;
	int		tmp;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (2);
	tmp = open("tmp", O_RDONLY);
	if (tmp == -1)
		return (2);
	l = fork();
	if (l == -1)
		return (2);
	if (l == 0)
	{
		if (dup2(tmp, STDIN_FILENO) == -1)
			return (2);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (2);
		close_fds((int []){pipefd[0], pipefd[1], tmp}, 3);
		execve(cmd[0], &cmd[1], envp);
		exit(2);
	}
	return (parent(pipefd, tmp, l));
}

static int	handle(int ac, char **av, char **envp, int infd)
{
	int		i;
	char	**cmd;

	i = cmd_index(infd);
	while (++i < ac - 1)
	{
		cmd = get_cmd(av[i], envp);
		if (!cmd)
			return (3);
		if (child(cmd, envp) == 2)
		{
			free_2d(cmd);
			return (2);
		}
		free_2d(cmd);
	}
	return (print_out(infd, ac, av));
}

static int	pipex(int ac, char **av, char **envp)
{
	int		infd;

	if (ac < 5)
		return (1);
	if (ft_strncmp(av[1], "here_doc", 9) != 0)
		infd = open(av[1], O_RDONLY);
	else
		infd = STDIN_FILENO;
	if (infd == -1)
		return (2);
	if (init_tmp(infd, av[2]) == 2)
		return (2);
	return (handle(ac, av, envp, infd));
}

int	main(int ac, char **av, char **envp)
{
	int	status;

	status = pipex(ac, av, envp);
	if (!access("tmp", F_OK))
		unlink("tmp");
	if (status)
		ft_putstr_fd("\t~~~~~~~~~~ Error ~~~~~~~~~~\n\t", 2);
	else
		return (0);
	if (status == 1)
		ft_putstr_fd("Incorrect number of arguments\n", 2);
	else if (status == 2)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	else if (status == 3)
		ft_putstr_fd("command not found\n", 2);
}
