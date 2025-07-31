/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:49:41 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/31 19:04:18 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell)
{
	shell->cmd = NULL;
	shell->exit_value = 0;
	shell->in_quote = false;
	shell->token.head = NULL;
	shell->token.current = NULL;
}

bool	is_builtin(char *cmd)
{
	const char	*valid[] = {"env", "export", "pwd", "unset", "cd",
		"exit", "echo", NULL};
	int			i;

	i = 0;
	while (valid[i])
	{
		if (ft_strcmp((char *)valid[i], cmd) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	new_exit_code(t_shell *shell, int status)
{
	shell->exit_value = status;
}

void	status_code_update(t_shell *shell)
{
	if (g_current_child_pid == SIGINT)
		shell->exit_value = 130;
	else if (g_current_child_pid == SIGQUIT)
		shell->exit_value = 131;
	g_current_child_pid = -1;
}

int	parser_builtin(t_shell *root, t_cmd *cmd)
{
	int		fd;

	if (ft_strcmp(cmd->argv[0], "env") == 0 && cmd->argc != 1)
		return (write(2, "Invalid command\n", 16), 1);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
	{
		fd = which_fd(root);
		return (print_env_list_fd(root->env, ENV, fd), 1);
	}
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (new_exit_code(root, ft_export(root, cmd)), 1);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (new_exit_code(root, ft_pwd(root, cmd)), 1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (new_exit_code(root, ft_unset(root, cmd)), 1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (new_exit_code(root, ft_cd(root, cmd)), 1);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exit(root, cmd), 1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (new_exit_code(root, ft_echo(root, cmd)), 1);
	return (0);
}
