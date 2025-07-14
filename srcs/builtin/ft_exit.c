/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:20:05 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/14 16:42:12 by mbrighi          ###   ########.fr       */
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
		free_matrix(root->envp);
	rl_clear_history();
}

void	too_much_args(t_shell *root, t_cmd *cmd, int len)
{
	write(2, "exit\nbash: exit: ", 17);
	write(2, cmd->argv[1], len);
	write(2, ": numeric argument required\n", 28);
	clean_exit(root);
	cleanup_shell(root);
	exit(2);
}

void	ft_exit(t_shell *root, t_cmd *cmd)
{
	long long int	exit_code = 0;
	size_t			len;

	len = ft_strlen(cmd->argv[1]);
	if (cmd->argc > 2 && what_is(cmd->argv[1], (int)len) == 2)
	{
		write(2, "exit\nbash: exit: too many arguments\n", 36);
		root->exit_value = 1;
		return ;
	}
	if (cmd->argc > 1)
	{
		if (what_is(cmd->argv[1], (int)len) != 2)
			too_much_args(root, cmd, len);
		exit_code = ft_atoi_ll(cmd->argv[1]);
	}
	write(1, "exit\n", 5);
	clean_exit(root);
	cleanup_shell(root);
	exit((unsigned char)exit_code);
}

