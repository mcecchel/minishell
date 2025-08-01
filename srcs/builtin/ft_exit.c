/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:20:05 by mbrighi           #+#    #+#             */
/*   Updated: 2025/08/01 15:51:39 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	goodbye_my_dear(t_shell *root)
{
	write(1, "exit\n", 5);
	clean_exit(root);
	cleanup_shell(root);
	exit((unsigned char)root->exit_value);
}

void	clean_exit(t_shell *root)
{
	if (root->cmd)
		close_cmd_fds(root->cmd);
	if (root->env)
		free_env_list(root->env);
	if (root->envp)
		free_matrix(root->envp);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(root->original_stdin);
	close(root->original_stdout);
}

void	too_many_args(t_shell *root, t_cmd *cmd, int len)
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
	long long int	exit_code;
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
			too_many_args(root, cmd, len);
		exit_code = ft_atoi_ll(cmd->argv[1]);
		root->exit_value = exit_code;
		goodbye_my_dear(root);
	}
	goodbye_my_dear(root);
}

/* Exit codes reference:
 * 126: Command found but not executable (permission denied)
 * 127: Command not found
 * 130: Terminated by Ctrl+C (SIGINT)
 */
