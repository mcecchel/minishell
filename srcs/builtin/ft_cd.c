/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:22:07 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/30 18:05:33 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env *find_env(t_env *env, char *to_change)
{
	while (env)
	{
		if (env->var && ft_strcmp(env->var, to_change) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	change_env(t_shell *root, char *old_path, char *current_path)
{
	t_env *pwd;
	t_env *oldpwd;

	pwd = find_env(root->env, "PWD");
	if (pwd)
	{
		if (pwd->arg)
			free(pwd->arg);
		pwd->arg = ft_strdup(current_path);
	}
	oldpwd = find_env(root->env, "OLDPWD");
	if (oldpwd)
	{
		if (oldpwd->arg != NULL)
			free(oldpwd->arg);
		oldpwd->arg = ft_strdup(old_path);
		oldpwd->ex_env = 1;
	}
}


int	ft_cd(char *new_path, t_shell *root)
{
	char	*current_path;
	char	*old_path;

	old_path = getcwd(NULL, 0);
	ft_printf("%s\n", old_path);
	if (chdir(new_path) == -1)
	{
		perror("cd");
		free(old_path);
		return (1);
	}
	current_path = getcwd(NULL, 0);
	ft_printf("%s\n", current_path);
	if (new_path[0] == '-' && new_path[1] == '\0')
		current_path = old_path;
	change_env(root, old_path, current_path);
	free(current_path);
	free(old_path);
	return(0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char	**mini_env;
// 	int 	i;
// 	int		k;

// 	i = 0;
// 	k = 0;
// 	mini_env = copy_env(envp);
// 	//print_env(mini_env);
// 	//ft_cd("Libft/ft_printf", mini_env);
// 	ft_cd(argv[1], mini_env);
// 	printf("//////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
// 	sort_env(mini_env);
// 	print_env(mini_env);
// 	free_matrix(mini_env);
// 	return(0);
// }
