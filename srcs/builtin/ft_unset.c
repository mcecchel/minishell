/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:31:15 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/19 23:55:56 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *to_remove, t_shell root)
{
	int i;
	int	j;

	i = 0;

	while(root.env[i] != NULL)
	{
		if ((ft_strncmp(root.env[i], to_remove, ft_strlen(to_remove)) == 0) &&
		(root.env[i][ft_strlen(to_remove)] == '='))
		{
			free(root.env[i]);
			j = i;
			while (root.env[j] != NULL)
			{
				root.env[j] = root.env[j+1];
				j++;
			}
		}
		i++;
	}	
}

// int main(int argc, char **argv, char **envp)
// {
// 	char	**mini_env;
// 	int 	i;
// 	int		k;

// 	i = 0;
// 	k = 0;
// 	mini_env = copy_env(envp);
// 	print_env(mini_env);
// 	//ft_cd("Libft", mini_env);
// 	ft_unset(argv[1], mini_env);
// 	printf("//////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
// 	print_env(mini_env);
// 	free_matrix(mini_env);
// 	return(0);
// }
