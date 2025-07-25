/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:03:55 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/24 14:47:11 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "builtin.h"

extern int	g_current_child_pid;

void	status_code_update(t_shell *shell);

#endif
