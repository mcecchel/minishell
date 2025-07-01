/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:20:05 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/01 15:47:09 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_shell *root)
{
	if (root->cmd)
		close_cmd_fds(root->cmd);
	if (root->env)
		free_env_list(root->env);
	if (root->envp)
		free_split(root->envp);
	rl_clear_history();
}

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
			clean_exit(root);
			exit(2);
		}
		exit_code = ft_atoi_ll(root->cmd->argv[1]);
	}
	write(1, "exit\n", 5);
	clean_exit(root);
	cleanup_shell(root);
	exit(exit_code % 256);
}

	// if (cmd_no_permission or no -x permission) //ex. root
	// 	exit(126);
	// if (cmd_not_found)
	// 	exit (127);
	// if (ctrl+C)
	// 	exit (130);




