/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:22:22 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/16 20:21:36 by mcecchel         ###   ########.fr       */
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
void	free_matrix(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	close_all_cmd_fds(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current)
	{
		close_cmd_fds(current);
		current = current->next;
	}
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

t_token	*ft_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
