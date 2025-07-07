/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:30:08 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/07 16:55:58 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <readline/history.h>
#include <signal.h>

// Variabile globale
volatile pid_t current_child_pid = -1;

void sigint_handler(int sig)
{
	(void)sig;
	if (current_child_pid > 0)
	{
		kill(current_child_pid, SIGKILL);  // Termina il processo figlio
		current_child_pid = -1;
	}
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);          // Pulisce la riga corrente
	rl_on_new_line();                // Si prepara a una nuova riga
	rl_redisplay();                  // Mostra il prompt di nuovo
}

void debug_cmds(t_cmd *cmd_list)
{
	int cmd_index = 0;
	t_cmd *current = cmd_list;

	if (!DEBUG)
		return ;
	while (current)
	{
		printf_debug("Command %d:\n", cmd_index++);
		printf_debug("  Path: %s\n", current->cmd_path);
		printf_debug("  Arguments: ");
		int i = 0;
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
	if (token->type == CMD) return ("CMD");
	else if (token->type == ARG) return ("ARG");
	else if (token->type == FLAG) return ("FLAG");
	else if (token->type == PIPE) return ("PIPE");
	else if (token->type == RED_IN) return ("RED_IN");
	else if (token->type == RED_OUT) return ("RED_OUT");
	else if (token->type == APPEND) return ("APPEND");
	else if (token->type == HEREDOC) return ("HEREDOC");
	else if (token->type == QUOTE) return ("QUOTE");
	else if (token->type == DQUOTE) return ("DQUOTE");
	else return ("UNKNOWN");
}

// Funzione di debug 2
void	debug_tokens(t_token *token)
{
	if (!DEBUG)
		return ;
	int i = 0;
	while (token)
	{
		printf_debug("[%d] Token: \"%s\" | Type: %s", i, token->value, obtain_token_type(token));
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
}

void print_pwd(t_env *env_list)
{
	t_env *pwd = find_env(env_list, "PWD");

	if (pwd && pwd->arg)
		ft_printf("%s\n", pwd->arg);
	else
		ft_printf("PWD not found or has no value\n");
		
	t_env *oldpwd = find_env(env_list, "OLDPWD");
	if (oldpwd && oldpwd->arg)
		ft_printf("%s\n", oldpwd->arg);
	else
		ft_printf("OLDPWD not found or has no value\n");
}

int	parser_builtin(t_shell *root)
{
	root->exit_value = 0;
	if (ft_strcmp(root->cmd->argv[0], "env") == 0)
		return (print_env_list(root->env, ENV), 1);
	if (ft_strcmp(root->cmd->argv[0], "export") == 0)
		return (ft_export(root), 1);
	if (ft_strcmp(root->cmd->argv[0], "pwd") == 0)
		return (root->exit_value = ft_pwd(root), 1);
	if (ft_strcmp(root->cmd->argv[0], "unset") == 0)
		return (root->exit_value = ft_unset(root), 1);
	if (ft_strcmp(root->cmd->argv[0], "cd") == 0)
		return (root->exit_value = ft_cd(root), 1);
	if (ft_strcmp(root->cmd->argv[0], "exit") == 0)
		return (ft_exit(root), 1);
	if (ft_strcmp(root->cmd->argv[0], "echo") == 0)
		return (root->exit_value = ft_echo(root), 1);
	if (ft_strchr(root->cmd->argv[0], '='))
		return (add_env(root, root->cmd->argv[0], VAR), 1);
	return (0);
}
void	reading(t_shell shell)
{

	char	*line;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write (1, "exit\n", 5);
			clean_exit(&shell);
			cleanup_shell(&shell);
			exit (1);
		}
		// Ignora linee vuote
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		add_history(line);
		// Tokenizza l'input
		if (!tokenize_input(&shell.token, line, &shell))
		{
			cleanup_shell(&shell);
			free(line);
			continue;
		}
		// Debug opzionale
		printf_debug("Generated tokens:\n");
		debug_tokens(shell.token.head);

		// Parsing
		shell.cmd = parse_tokens(shell.token.head, &shell);
		if (!shell.cmd)
		{
			cleanup_shell(&shell);
			free(line);
			continue;
		}
		// Debug opzionale
		printf_debug("\nGenerated commands:\n");
		debug_cmds(shell.cmd);
		
		// Processa gli heredoc prima dell'esecuzione
		if (!process_heredocs(&shell))
		{
			cleanup_shell(&shell);
			free(line);
			continue;
		}
		
		// print_envp_char(shell.envp);
		
		// Gestisci built-in nel processo padre solo se è un comando singolo
		if (shell.cmd && !shell.cmd->next && parser_builtin(&shell))
		{
			// Built-in eseguita nel processo padre per modificare lo stato della shell
		}
		else
		{
			// Comandi esterni o pipeline (incluse built-in in pipeline)
			execute_command_list(&shell);
		}

		cleanup_shell(&shell);
		free(line);
	}
}

void process_shell_input(t_shell *shell)
{
	char *line;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			clean_exit(shell);
			cleanup_shell(shell);
			exit(1);
		}
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		add_history(line);
		if (!tokenize_input(&shell->token, line, shell))
		{
			ft_printf("Error: Tokenization failed\n");
			cleanup_shell(shell);
			free(line);
			continue;
		}
		printf_debug("Generated tokens:\n");
		debug_tokens(shell->token.head);

		shell->cmd = parse_tokens(shell->token.head, shell);
		if (!shell->cmd)
		{
			cleanup_shell(shell);
			free(line);
			continue;
		}
		printf_debug("\nGenerated commands:\n");
		debug_cmds(shell->cmd);
		if (!process_heredocs(shell))
		{
			cleanup_shell(shell);
			free(line);
			continue;
		}
		execute_command_list(shell);
		cleanup_shell(shell);
		free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_env	*env = (t_env *){0};
	shell = (t_shell){0};
	env = copy_env(envp);
	copy_system_envp_to_shell(envp, &shell);
	//print_envp_char(shell.envp);
	shell.env = env;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN); 
	init_shell(&shell);
	reading(shell);
	cleanup_shell(&shell);
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char *read_line;
// 	t_env	*env = (t_env *){0};
// 	t_shell	*root;
// 	int i = 0;
// 	//int a;
// 	//char	*tryunset;

// 	root = ft_calloc(1, sizeof(t_shell));
// 	env = copy_env(envp);
// 	rool.env = env;
// 	(void)argc;
// 	(void)argv;
// 	while(1)
// 	{
// 		read_line = readline("");

// 		if (read_line == NULL)
// 		{
// 			printf("\nexit\n");
// 			free_env_list(env);
// 			free (root);
// 			break;
// 		}
// 		parser_builtin(root, read_line);
// 		free(read_line);
// 		i++;
// 	}
//     return (0);
// }
