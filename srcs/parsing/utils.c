/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:22:22 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/25 18:15:04 by mbrighi          ###   ########.fr       */
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

void	copy_system_envp_to_shell(char **system_envp, t_shell *shell)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (system_envp[count])
		count++;
	shell->envp = ft_calloc(count + 1, sizeof(char *));
	if (!shell->envp)
		return;
	while (i < count)
	{
		shell->envp[i] = ft_strdup(system_envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
}

