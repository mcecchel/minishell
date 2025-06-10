/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:30:08 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/10 15:03:02 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <readline/history.h>
#include <signal.h>

void sigint_handler(int sig)
{
	(void)sig;
	// Vai a capo e mostra di nuovo il prompt
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);          // Pulisce la riga corrente
	rl_on_new_line();                // Si prepara a una nuova riga
	rl_redisplay();                  // Mostra il prompt di nuovo
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

void	parser_builtin(t_shell *root, char *read_line)
{
	
	char *try = NULL;

	if (ft_strcmp(read_line, "env") == 0)
		print_env_list(root->env, true);
	if (ft_strncmp(read_line, "export", 6) == 0)
	{
		//a = ft_strcmp(read_line, "export");
		//ft_printf("a is %d\n", ft_strcmp(read_line, "export"));
		if (ft_strcmp(read_line, "export") == 0)
		{
			
			//ft_printf("CIAO\n");
			print_env_list(root->env, false);
		}
		else
		{
			try = ft_substr(read_line, 7, (ft_strlen(read_line) - 7));
			ft_export(root, try);
			ft_printf("to add is %s\n", try);
			if (try != NULL)
				free (try);
		}
	}
	if (ft_strcmp(read_line, "pwd") == 0)
		ft_pwd();
	if (ft_strncmp(read_line, "unset", 5) == 0)
	{
		try = ft_substr(read_line, 6, (ft_strlen(read_line) - 6));
		ft_unset(root, try);
		if (try != NULL)
				free (try);
	}
	if (ft_strncmp(read_line, "cd ", 3) == 0)
	{
		//ft_printf("%s", ft_substr(read_line, 3, (ft_strlen(read_line) - 3)));
		try = ft_substr(read_line, 3, (ft_strlen(read_line) - 3));
		ft_cd(try, root);
		if (try != NULL)
				free (try);
	}
	if (ft_strncmp(read_line, "exit", 4) == 0)
	{
		try = ft_substr(read_line, 5, (ft_strlen(read_line) - 5));
		free(read_line);
		ft_exit(try, root);
	}
		// if (i == 4)
		// 	print_env_list(env);
		//printf("%s\n", read_line);
}


int main(int argc, char **argv, char **envp)
{
    char *read_line;
    read_line = readline("Prompt > ");
    printf("%s\n", read_line);
	free(read_line);
    return (0);
}
