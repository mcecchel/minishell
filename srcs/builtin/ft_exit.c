/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:20:05 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/25 16:47:27 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *root)
{
	long long int	exit_code = 0;
	size_t			len;

	len = ft_strlen(root->cmd->argv[1]);
	if (root->cmd->argc > 2 && what_is(root->cmd->argv[1], (int)len) == 2)
	{
		write(2, "exit\nbash: exit: too many arguments\n", 36);
		return ;
	}
	if (root->cmd->argc > 1)
	{
		if (what_is(root->cmd->argv[1], (int)len) != 2)
		{
			write(2, "exit\nbash: exit: ", 17);
			write(2, root->cmd->argv[1], len);
			write(2, ": numeric argument required\n", 28);
			rl_clear_history();
			exit(2);
		}
		exit_code = ft_atoi_ll(root->cmd->argv[1]);
	}
	write(1, "exit\n", 5);
	cleanup_shell(root);
	rl_clear_history();
	exit(exit_code % 256);
}

	// if (cmd_no_permission or no -x permission) //ex. root
	// 	exit(126);
	// if (cmd_not_found)
	// 	exit (127);
	// if (ctrl+C)
	// 	exit (130);




