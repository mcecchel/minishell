/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:30:08 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/24 17:28:24 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <readline/history.h>
#include <signal.h>

// Variabile globale
int	g_current_child_pid = -1;

void	sigint_handler(int sig)
{
	(void)sig;
	g_current_child_pid = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	debug_cmds(t_cmd *cmd_list)
{
	int		cmd_index;
	t_cmd	*current;
	int		i;

	cmd_index = 0;
	current = cmd_list;
	if (!DEBUG)
		return ;
	while (current)
	{
		printf_debug("Command %d:\n", cmd_index++);
		printf_debug("  Path: %s\n", current->cmd_path);
		printf_debug("  Arguments: ");
		i = 0;
		while (current->argv && current->argv[i])
		{
			printf_debug("\"%s\" ", current->argv[i]);
			i++;
		}
		printf_debug("\n");
		printf_debug("  Infile: %d\n", current->infile);
		printf_debug("  Outfile: %d\n", current->outfile);
		current = current->next;
	}
}

const char	*obtain_token_type(t_token *token)
{
	if (!DEBUG)
		return ("NULL");
	if (token->type == CMD)
		return ("CMD");
	else if (token->type == ARG)
		return ("ARG");
	else if (token->type == FLAG)
		return ("FLAG");
	else if (token->type == PIPE)
		return ("PIPE");
	else if (token->type == RED_IN)
		return ("RED_IN");
	else if (token->type == RED_OUT)
		return ("RED_OUT");
	else if (token->type == APPEND)
		return ("APPEND");
	else if (token->type == HEREDOC)
		return ("HEREDOC");
	else if (token->type == QUOTE)
		return ("QUOTE");
	else if (token->type == DQUOTE)
		return ("DQUOTE");
	else
		return ("UNKNOWN");
}

// Funzione di debug 2
void	debug_tokens(t_token *token)
{
	int	i;

	if (!DEBUG)
		return ;
	i = 0;
	while (token)
	{
		printf_debug("[%d] Token: \"%s\" | Type: %s", i, token->value,
			obtain_token_type(token));
		if (token->is_quoted)
			printf_debug(" (QUOTED)");
		printf_debug("\n");
		token = token->next;
		i++;
	}
}

void	init_shell(t_shell *shell)
{
	shell->cmd = NULL;
	shell->exit_value = 0;
	shell->in_quote = false;
	shell->token.head = NULL;
	shell->token.current = NULL;
}
void	cleanup_shell(t_shell *shell)
{
	if (shell->cmd)
	{
		free_cmd_list(shell->cmd);
		shell->cmd = NULL;
	}
	if (shell->token.head)
	{
		free_tokens(shell->token.head);
		shell->token.head = NULL;
		shell->token.current = NULL;
	}
	free(shell->line);
	shell->line = NULL;
}

void	print_pwd(t_env *env_list)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_env(env_list, "PWD");
	if (pwd && pwd->arg)
		ft_printf("%s\n", pwd->arg);
	else
		ft_printf("PWD not found or has no value\n");
	oldpwd = find_env(env_list, "OLDPWD");
	if (oldpwd && oldpwd->arg)
		ft_printf("%s\n", oldpwd->arg);
	else
		ft_printf("OLDPWD not found or has no value\n");
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

int	parser_builtin(t_shell *root, t_cmd *cmd)
{
	int		fd;

	root->exit_value = 0;
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

void	reading(t_shell *shell)
{
	while (1)
	{
		shell->line = readline("minishell> ");
		status_code_update(shell);
		if (!shell->line)
		{
			write (1, "exit\n", 5);
			clean_exit(shell);
			cleanup_shell(shell);
			exit (1);
		}
		if (*shell->line == '\0')
		{
			free(shell->line);
			shell->line = NULL;
			continue ;
		}
		add_history(shell->line);
		if (!tokenize_input(&shell->token, &shell->line, shell))
		{
			cleanup_shell(shell);
			continue ;
		}
		printf_debug("Generated tokens:\n");
		debug_tokens(shell->token.head);
		shell->cmd = parse_tokens(shell->token.head, shell);
		if (!shell->cmd)
		{
			cleanup_shell(shell);
			continue ;
		}
		shell->cmd = optimize_command_list(shell->cmd);
		printf_debug("\nGenerated commands:\n");
		debug_cmds(shell->cmd);
		if (shell->cmd && !shell->cmd->next && (is_dummy_command(shell->cmd) || is_builtin(shell->cmd->cmd_path)))
		{
			if (is_builtin(shell->cmd->cmd_path))
			{
				if (shell->cmd->infile != -1)
					if (dup2(shell->cmd->infile, STDIN_FILENO) == -1)
						;
				if (shell->cmd->outfile != -1)
					if (dup2(shell->cmd->outfile, STDOUT_FILENO) == -1)
						;
				parser_builtin(shell, shell->cmd);
				if (shell->cmd->infile != -1)
					dup2(shell->original_stdin, STDIN_FILENO);
				if (shell->cmd->outfile != -1)
					dup2(shell->original_stdout, STDOUT_FILENO);
			}
		}
		else
			execute_command_list(shell);
		cleanup_shell(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_env	*env;

	shell = (t_shell){0};
	env = (t_env *){0};
	env = copy_env(envp);
	copy_system_envp_to_shell(envp, &shell);
	shell.env = env;
	(void)argc;
	(void)argv;
	shell.original_stdin = dup(STDIN_FILENO);
	shell.original_stdout = dup(STDOUT_FILENO);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	init_shell(&shell);
	reading(&shell);
	cleanup_shell(&shell);
	clean_exit(&shell);
	return (0);
}
