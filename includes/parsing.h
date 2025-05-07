/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianna <marianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:02:45 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/07 15:52:59 by marianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

// usare enum perche' cosi' non c'e' bisogno di specificare il tipo delle variabili
typedef enum e_token
{
	// PAROLE
	CMD,
	ARG,
	OPTION,
	FLAG,
	// OPERATORI DI CONTROLLO
	PIPE,
	// OPERATORI DI REDIREZIONE
	RED_IN,
	RED_OUT,
	RED_APPEND,
	RED_HEREDOC,
	// PARENTESI E SIMBOLI SPECIALI
	QUOTE,
	DQUOTE,
	UNKNOWN,
}			t_token;

typedef struct s_cmd
{
    char			*cmd_path;
    char			**argv;
//    int			fd_pipe[2];
    int				pid;
	struct s_cmd	*next;	
}					t_cmd;

typedef struct s_shell
{
    char	**envp;
    t_cmd	*cmd;
    int		n_cmds;
	t_token	token;

}			   t_shell;

# endif