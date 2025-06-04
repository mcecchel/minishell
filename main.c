/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:30:08 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/04 16:42:36 by mbrighi          ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	char *read_line;
	t_env	*env = (t_env *){0};
	t_shell	*root;
	int i = 0;
	//int a;
	//char	*tryunset;

	root = ft_calloc(1, sizeof(t_shell));
	env = copy_env(envp);
	root->env = env;
	(void)argc;
	(void)argv;
	//signal(SIGINT, sigint_handler);
	//signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		read_line = readline("");

		if (read_line == NULL)
		{
			printf("\nexit\n");
			free_env_list(env);
			break;
		}
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
				continue;
			}
			else
			{
				ft_export(root, ft_substr(read_line, 7, (ft_strlen(read_line) - 7)));
				ft_printf("to add is %s\n", ft_substr(read_line, 7, (ft_strlen(read_line) - 7)));
			}
		}
		if (ft_strcmp(read_line, "PWD") == 0)
			ft_unset(&root->env, read_line);
		if (ft_strncmp(read_line, "cd ", 3) == 0)
		{
			//ft_printf("%s", ft_substr(read_line, 3, (ft_strlen(read_line) - 3)));
			ft_cd(ft_substr(read_line, 3, (ft_strlen(read_line) - 3)), root);
		}
		// if (i == 4)
		// 	print_env_list(env);
		//printf("%s\n", read_line);
		free(read_line);
		i++;
	}
	return (0);
}
