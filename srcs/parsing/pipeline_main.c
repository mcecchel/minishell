/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:57:57 by mbrighi           #+#    #+#             */
/*   Updated: 2025/08/01 19:58:49 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fds_on_error(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		close_all_cmd_fds(current);
		current = current->next;
	}
}

int	handle_fork_creation(t_cmd *current)
{
	current->pid = fork();
	if (current->pid == -1)
	{
		perror("Fork error");
		return (-1);
	}
	return (0);
}

int	handle_standard_advance(t_token **tok, t_cmd **cmd_list,
				t_cmd **current, t_shell *shell)
{
	int	ok;

	ok = process_token(*tok, cmd_list, current, shell);
	if (!ok)
		return (0);
	*tok = (*tok)->next;
	return (1);
}
