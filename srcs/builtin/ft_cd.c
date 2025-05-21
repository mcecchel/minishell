/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:22:07 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/21 17:42:39 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(t_shell root, char *old_path, char *current_path)
{
	int i;

	i = 0;
	while (root.env[i])
	{
		if (ft_strnstr(root.env[i], "PWD=", 4) != 0)
		{
			free (root.env[i]);
			root.env[i] = ft_strdup(current_path);
			break;
		}
		i++;
	}
	i = 0;
	while (root.env[i])
	{
		if (ft_strnstr(root.env[i], "OLDPWD=", 7) != 0)
		{
			free (root.env[i]);
			root.env[i] = ft_strdup(old_path);
			break;
		}
		i++;
	}
}

int	ft_cd(char *new_path, t_shell root)
{
	char	*current_path;
	char	*old_path;

	old_path = getcwd(NULL, 0);
	old_path = ft_strjoin_free_s2("OLDPWD=", old_path);
	if (chdir(new_path) == -1)
	{
		perror("cd");
		free(old_path);
		return (1);
	}
	current_path = getcwd(NULL, 0);
	current_path = ft_strjoin_free_s2("PWD=", current_path);
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
