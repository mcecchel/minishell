/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:03:55 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/15 18:50:43 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int current_child_pid;

# include "parsing.h"
// # include "exec.h"
# include "builtin.h"

void	status_code_update(t_shell *shell);

#endif
