/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:31:15 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/01 16:18:23 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell *shell)
{
	t_env	*current;

	if (!shell || !shell->cmd->argv)
		return (1);
	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->var, shell->cmd->argv[1]) == 0)
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				shell->env = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(current->var);
			if (current->arg)
				free(current->arg);
			free(current);
			return (0);
		}
		current = current->next;
	}
	return (0);
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
// 	printf("///////////////////////////////////////////////////////////////\n");
// 	print_env(mini_env);
// 	free_matrix(mini_env);
// 	return(0);
// }
