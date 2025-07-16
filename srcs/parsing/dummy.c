/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:49:10 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/16 20:09:45 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Controlla se un comando è dummy (vuoto)
int	is_dummy_command(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd_path)
		return (1);
	if (ft_strlen(cmd->cmd_path) == 0)
		return (1);
	if (cmd->dummy_on == 1)
		return (1);
	return (0);
}

// Libera un singolo comando
void	free_single_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	if (cmd->argv)
	{
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	free(cmd);
}

// Merge dummy command con il comando reale successivo
void	merge_dummy_to_real(t_cmd *dummy, t_cmd *real)
{
	if (!dummy || !real || !is_dummy_command(dummy))
		return ;
	if (dummy->infile != -1)
	{
		if (real->infile != -1)
			close(real->infile);
		real->infile = dummy->infile;
		dummy->infile = -1;
	}
	if (dummy->outfile != -1)
	{
		if (real->outfile != -1)
			close(real->outfile);
		real->outfile = dummy->outfile;
		dummy->outfile = -1;
	}
	if (dummy->heredoc_delimiter)
	{
		if (real->heredoc_delimiter)
			free(real->heredoc_delimiter);
		real->heredoc_delimiter = dummy->heredoc_delimiter;
		dummy->heredoc_delimiter = NULL;
	}
}

t_cmd	*remove_dummy_from_list(t_cmd *cmd_list, t_cmd *to_remove)
{
	t_cmd	*current;
	t_cmd	*prev;

	current = cmd_list;
	prev = NULL;
	if (!cmd_list || !to_remove)
		return (cmd_list);
	if (cmd_list == to_remove)
	{
		cmd_list = cmd_list->next;
		free_single_cmd(to_remove);
		return (cmd_list);
	}
	while (current && current != to_remove)
	{
		prev = current;
		current = current->next;
	}
	if (current == to_remove)
	{
		prev->next = current->next;
		free_single_cmd(to_remove);
	}
	return (cmd_list);
}

// Ottimizza la lista dei comandi rimuovendo i dummy e facendo merge
t_cmd	*optimize_command_list(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		if (is_dummy_command(current) && current->next
			&& !is_dummy_command(current->next))
		{
			merge_dummy_to_real(current, current->next);
			cmd_list = remove_dummy_from_list(cmd_list, current);
			current = cmd_list;
		}
		else
			current = current->next;
	}
	return (cmd_list);
}
