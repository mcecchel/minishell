/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:22:22 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/10 12:31:23 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

// Funzione per liberare matrice di stringhe
void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	close_cmd_fds(t_cmd *cmd)
{
	if (cmd->infile != -1)
	{
		close(cmd->infile);
		cmd->infile = -1;
	}
	if (cmd->outfile != -1)
	{
		close(cmd->outfile);
		cmd->outfile = -1;
	}
}
