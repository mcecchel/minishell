/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:02:45 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/21 17:54:20 by mcecchel         ###   ########.fr       */
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
	int				argc;
	int				infile;
	int				outfile;
	int				pid;
	//int			fd_pipe[2];
	struct s_cmd	*next;
}					 t_cmd;

typedef struct s_shell
{
    char	**envp;
    t_cmd	*cmd;
    int		n_cmds;
	t_token	token;
	bool	in_quote;

}			   t_shell;

// Funzioni parsing e lexer
t_token	*tokenize_input(t_token *token, char *line);
t_cmd	*parse_tokens(t_token *token_list, t_cmd *cmd);
void	debug_tokens(t_token *token);
void	debug_cmds(t_cmd *cmd_list);
void	free_tokens(t_token *token);
void	free_cmd_list(t_cmd *cmd);
t_cmd	*init_new_cmd(t_cmd *cmd);
void	add_cmd(t_cmd *cmd, t_cmd *new_cmd);
char	*extract_word(char *line, int *index);
char	*extract_quote(char *line, int *index);
char	*extract_operator(char *line, int *index);
t_token_type	classify_token(char *str, int is_first_token);
t_token	*add_token(t_token *token, char *content);
void	print_token_type(t_token *token);
int		handle_heredoc(char *delimiter);

// Funzioni gestione comandi
int		is_space(char c);
int		find_spaces(char c);
char	*find_env_path(t_shell *shell);
void	free_split(char **split);
void	close_cmd_fds(t_cmd *cmd);
void	close_cmd_pipes(t_cmd *cmd);
int		is_valid_command(t_cmd *cmd, char *command);
char	**get_paths(t_shell *shell);
char	*search_command(char **paths, char *cmd);
char	*get_cmd_path(t_shell *shell, t_cmd *cmd, char *command);
void	handle_exec_error(t_cmd *cmd, char **command, char *path);
void	execute_cmd(t_shell *shell, t_cmd *cmd);
void	execute_command_list(t_shell *shell);

# endif
