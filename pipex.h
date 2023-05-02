/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:46:27 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/05/02 20:44:04 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

char		**get_cmd(char *s, char **envp);
void		free_2d(char **split);
void		read_write(int from_fd, int to_fd);
void		close_fds(int fd[], int n);
int			print_out(int infd, int ac, char **av);
int			init_tmp(int infd, char *delim);
int			cmd_index(int infd);

#endif