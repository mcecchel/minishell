/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:20:05 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/15 14:47:57 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_exit(char *arg)
{
	//kill_em_all(distruggi tutto quello che hai fatto prima, bro: freea cio che devi freeare e bone)
	int	exit_code;

	if (arg[0] == '0' && arg[1] == '\0')
	{
		write (1, "exit\n", 5);
		exit (0);
	}
	exit_code = ft_atoi(arg); //modifica atoi per 
	if (!is_digit(arg)) // first arg must not be a num
	{
		write (2, "exit\n", 5);
		write (2, "bash: exit: ", 12);
		write (2, arg, ft_strlen(arg));
		write (2, ": numeric argument required\n", 28);
		exit (2);
	}
	if (is_digit(arg) && arg > 1)
	{
		write (1, "exit\n", 5);
		write (1, "bash: exit: ", 12);
		write (1, ": too many arguments\n", 21);
		return (0);
	}
	
	// if (cmd_no_permission) //ex. root
	// 	exit(126);
	// if (cmd_not_found)
	// 	exit (127);
	// if (ctrl+C)
	// 	exit (130);
	if (exit_code != 0 && exit_code <= 255)
		exit (exit_code);
	if (exit_code >= 255)
		exit (exit_code % 256);
}

