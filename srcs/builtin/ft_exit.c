/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:20:05 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/05 16:01:19 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *arg, t_shell *root)
{
	int	exit_code;

	if (what_is(arg, ft_strchr(arg, ' ')) == 2
		|| what_is(arg, ft_strchr(arg, '\t')) == 2)
	{
		write (1, "exit\n", 5);
		write (1, "bash: exit: ", 12);
		write (1, ": too many arguments\n", 21);
		return ;
	}
	free_env_list(root->env);
	if ((arg[0] == '0' && arg[1] == '\0') || arg == NULL)
	{
		write (1, "exit\n", 5);
		free (arg);
		exit (0);
	}
	if (what_is(arg, ((int)ft_strlen(arg)) == 2))
		exit_code = ft_atoi(arg);
	// if (!ft_isalpha) // first arg must not be a num
	// {
	// 	write (2, "exit\n", 5);
	// 	write (2, "bash: exit: ", 12);
	// 	write (2, arg, ft_strlen(arg));
	// 	write (2, ": numeric argument required\n", 28);
	// 	exit (2);
	// }
	//exit_code = ft_atoi(arg); //modifica atoi per 
	// if (cmd_no_permission or no -x permission) //ex. root
	// 	exit(126);
	// if (cmd_not_found)
	// 	exit (127);
	// if (ctrl+C)
	// 	exit (130);
	if (exit_code >= 0 && exit_code <= 255)
	{
		exit (exit_code);
	if (exit_code >= 255)
		exit (exit_code % 256);
}

