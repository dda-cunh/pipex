/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:33:59 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/05/02 20:55:29 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

int	cmd_index(int infd)
{
	if (infd)
		return (1);
	else
		return (2);
}

void	close_fds(int tmp[], int n)
{
	while (--n >= 0)
		close(tmp[n]);
}
