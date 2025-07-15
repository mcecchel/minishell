/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:31:15 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/15 17:35:43 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	t_env	*current;

	if (!shell || !(cmd->argc > 1) || !cmd->argv)
		return (1);
	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->var, cmd->argv[1]) == 0)
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				shell->env = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(current->var);
			if (current->arg)
				free(current->arg);
			free(current);
			update_shell_envp(shell);
			return (0);
		}
		current = current->next;
	}
	return (0);
}
