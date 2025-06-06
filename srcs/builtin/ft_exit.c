/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:20:05 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/06 16:10:24 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *arg, t_shell *root)
{
	long long int	exit_code;
	int				end;
	char 			*temp;

	exit_code = 0;
	temp = ft_strchr(arg, ' ');
	end = arg - temp;
	ft_printf("{%d}", end);
	ft_printf("LEGGI QUI: %d", what_is(arg, end));
	if (ft_strchr(arg, ' ') != NULL && what_is(arg, end) == 2)
	{
		write (1, "exit\n bash: exit: bash: exit: too many arguments\n", 49);
		return ;
	}
	free_env_list(root->env);
	if ((arg[0] == '0' && arg[1] == '\0') || arg == NULL)
	{
		write (1, "exit\n", 5);
		free (arg);
		exit (0);
	}
	else if (what_is(arg, end))
		exit_code = ft_atoi_ll(arg);
	else if (what_is(arg, end) != 2) // first arg must not be a num
	{
		write (2, "exit\nbash: exit: ", 17);
		write (2, arg, ft_strlen(arg));
		write (2, ": numeric argument required\n", 28);
		exit (2);
	}
	// if (cmd_no_permission or no -x permission) //ex. root
	// 	exit(126);
	// if (cmd_not_found)
	// 	exit (127);
	// if (ctrl+C)
	// 	exit (130);
	if ((exit_code >= 0 && exit_code <= 255) || !exit_code)
		exit (exit_code);
	if (exit_code >= 255)
		exit (exit_code % 256);
}




