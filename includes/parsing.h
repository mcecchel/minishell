/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:02:45 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/10 15:00:32 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */
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
	int				is_quoted; // simil buleana: 1 se quoted, 0 se non lo e'
}					t_token;

typedef struct s_cmd
{
	char			*cmd_path;
	char			**argv;
	int				argc;
	int				infile;
	int				outfile;
	int				pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	struct s_env	*prev;
	char			*var;
	char			*arg;
	int				ex_env;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
    t_env	*env;
	char	**envp;
    t_cmd	*cmd;
    int		n_cmds;
	t_token	token;
	bool	in_quote;
}			t_shell;

/* ************************************************************************** */
/*                          LEXER FUNCTIONS                                   */
/* ************************************************************************** */
// Tokenization functions
int				tokenize_input(t_token *token, char *line);
char			*extract_word(char *line, int *index);
char			*extract_quote(char *line, int *index, int *is_quoted);
char			*extract_operator(char *line, int *index);

// Token classification
t_token_type	classify_token(char *value, int is_first_token, int is_quoted);
t_token			*add_token(t_token *token, char *value, int is_quoted);

// Token utilities
void			print_token_type(t_token *token);
void			debug_tokens(t_token *token);
void			free_tokens(t_token *token);
int				handle_heredoc(char *delimiter);

/* ************************************************************************** */
/*                          PARSER FUNCTIONS                                 */
/* ************************************************************************** */

// Command parsing
t_cmd			*parse_tokens(t_token *token_list);
t_cmd			*init_new_cmd(void);
void			add_cmd(t_cmd *cmd, t_cmd *new_cmd);
void			add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd);
void			add_argument_to_cmd(t_cmd *cmd, char *arg);

// Redirection handling
int setup_input_redirection(t_cmd *cmd, char *filename);
int setup_output_redirection(t_cmd *cmd, char *filename, int append);
int setup_heredoc(t_cmd *cmd, char *delimiter);

// Command utilities
void			debug_cmds(t_cmd *cmd_list);
void			free_cmd_list(t_cmd *cmd);

/* ************************************************************************** */
/*                        COMMAND MANAGEMENT                                 */
/* ************************************************************************** */
// String utilities
int				is_space(char c);
int				find_spaces(char c);

// Environment handling
char			*find_env_path(t_shell *shell);
char			**get_paths(t_shell *shell);

// Command path resolution
char			*search_command(char **paths, char *cmd);
char			*get_cmd_path(t_shell *shell, t_cmd *cmd, char *command);
int				is_valid_command(t_cmd *cmd, char *command);

// Memory management
void			free_split(char **split);

// File descriptor management
void			close_cmd_fds(t_cmd *cmd);
void			close_cmd_pipes(t_cmd *cmd);

/* ************************************************************************** */
/*                         EXECUTION FUNCTIONS                               */
/* ************************************************************************** */
// Command execution
void			execute_cmd(t_shell *shell, t_cmd *cmd);
void			execute_command_list(t_shell *shell);
void			handle_exec_error(t_cmd *cmd, char **command, char *path);

int				main(int argc, char **argv, char **envp);

#endif
