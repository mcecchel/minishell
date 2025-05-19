/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:02:45 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/19 23:55:52 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

// usare enum perche' cosi' non c'e' bisogno di specificare il tipo delle variabili
typedef enum e_token_type
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
	APPEND,
	HEREDOC,
	// PARENTESI E SIMBOLI SPECIALI
	QUOTE,
	DQUOTE,
	UNKNOWN,
}			t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*head;
	struct s_token	*current;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			*cmd_path;
	char			**argv;
	int				infile;
	int				outfile;
	int				pid;
	//int			fd_pipe[2];
	struct s_cmd	*next;
}					 t_cmd;


typedef struct s_shell
{
    char	**env;
    t_cmd	*cmd;
    int		n_cmds;
	t_token	token;
	bool	in_quote;

}			   t_shell;

int	is_space(char c);

# endif
