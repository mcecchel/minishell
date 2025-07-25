/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:02:45 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/25 23:15:57 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
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

typedef enum e_var
{
	EXPORT,
	ENV,
	VAR,
}			t_var;

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
	int				dummy_on;
	int				pid;
	struct s_cmd	*next;
	char			*heredoc_delimiter;
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
	char	*line;
	t_env	*env;
	t_cmd	*cmd;
	char	**envp;
	int		exit_value;
	t_token	token;
	bool	in_quote;
	int		original_stdin;
	int		original_stdout;
}			t_shell;

typedef struct s_expand_ctx
{
	char		*str;
	int			*i;
	t_shell		*shell;
	char		*result;
	int			initial;
	char		quote;
}	t_expand_ctx;

typedef struct s_extract_ctx
{
	char		quote_char;
	int			start;
	int			end;
	int			quote_type;
	char		*res;
	char		*expanded;
}	t_extract_ctx;

typedef struct s_parse
{
	int		i;
	int		is_first;
	int		waiting;
	t_token	*token_list;
	t_shell	*shell;
	char	*line;
}	t_parse;

char	*expand_variables(char *line, t_shell *shell, int a, int b);
int		is_space(char c);
char	*extract_quote(char *line, int *i, int *quoted, t_shell *shell);
char	*extract_word(char *line, int *i, t_shell *shell);
char	*extract_operator(char *line, int *i);
t_token	*create_token(char *value, t_token_type type, int is_quoted);
void	add_token_to_list(t_token *token_list, t_token *new_token);
void	free_tokens(t_token *head);

/* ************************************************************************** */
/*                          LEXER FUNCTIONS                                   */
/* ************************************************************************** */
// Tokenization functions
int				tokenize_input(t_token *token, char **line, t_shell *shell);
char			*extract_word(char *line, int *index, t_shell *shell);
char			*extract_quote(char *line, int *index, int *is_quoted,
					t_shell *shell);
char			*extract_operator(char *line, int *index);

// Token classification
t_token_type	classify_token(char *value, int is_first_token, int is_quoted);
t_token			*add_token(t_token *token, char *value, int is_quoted);

// Token utilities
void			print_token_type(t_token *token);
void			debug_tokens(t_token *token);
void			free_tokens(t_token *token);

/* ************************************************************************** */
/*                          PARSER FUNCTIONS                                 */
/* ************************************************************************** */

// Command parsing
t_cmd			*parse_tokens(t_token *token_list, t_shell *shell);
t_cmd			*init_new_cmd(void);
void			add_cmd(t_cmd *cmd, t_cmd *new_cmd);
void			add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd);
void			add_argument_to_cmd(t_cmd *cmd, char *arg);
char			*get_cmd_path(t_shell *shell, t_cmd *cmd, char *command);

// Redirection handling
int				setup_input_redir(t_cmd *cmd, char *filename);
int				setup_output_redir(t_cmd *cmd, char *filename, int append);

// Command utilities
void			debug_cmds(t_cmd *cmd_list);
void			free_cmd_list(t_cmd *cmd);

/* ************************************************************************** */
/*                        COMMAND MANAGEMENT                                 */
/* ************************************************************************** */
// String utilities
int				is_space(char c);
int				find_spaces(char c);
void			free_split(char **split);
void			close_cmd_fds(t_cmd *cmd);

// Environment handling
char			*find_env_path(t_shell *shell);
char			**get_paths(t_shell *shell);
char			**env_list_to_array(t_env *env);
void			free_env_array(char **envp);
void			update_shell_envp(t_shell *shell);

/* ************************************************************************** */
/*                       VARIABLE EXPANSION                                  */
/* ************************************************************************** */
// Variable expansion functions
char			*expand_variables(char *str, t_shell *shell, int in_quotes, int initial_parse);
char			*get_env_value(t_shell *shell, char *var_name);
char			*extract_var_name(char *str, int *index);
int				should_expand_in_quotes(int quote_type);
char			*handle_special_vars(t_shell *shell, char *var_name);
//char			*process_variable(char *str, int *i, t_shell *shell, char *result, int initial_processing, char surrounded_by_quote);
char			*process_variable(t_expand_ctx *ctx);
char			*process_literal_text(char *str, int *i, char *result);

/* ************************************************************************** */
/*                         EXECUTION FUNCTIONS                               */
/* ************************************************************************** */
// Command execution
void			execute_cmd(t_shell *shell, t_cmd *cmd);
void			execute_command_list(t_shell *shell);
void			handle_exec_error(t_shell *shell, char **command, char *path);
void			cleanup_shell(t_shell *shell);
void			print_envp_char(char **envp);

int				main(int argc, char **argv, char **envp);

void			copy_system_envp_to_shell(char **system_envp, t_shell *shell);
void			fork_error_handler(t_shell *shell, t_cmd *cmd, int err, int exit_code);
int				which_fd(t_shell *shell);
void			free_matrix(char **str);
t_token			*ft_last(t_token *lst);

// Funzioni per gestione dummy command
int		is_dummy_command(t_cmd *cmd);
void	free_single_cmd(t_cmd *cmd);
void	merge_dummy_to_real(t_cmd *dummy, t_cmd *real);
t_cmd	*remove_dummy_from_list(t_cmd *cmd_list, t_cmd *to_remove);
t_cmd	*optimize_command_list(t_cmd *cmd_list);

void	close_all_cmd_fds(t_cmd *head);
void	sigint_handler(int sig);

/* INIZIO RIORGANIZZAZIONE .H */
/* ************************************************************************** */
/*                     HEREDOC FUNCTION PROTOTYPES                           */
/* ************************************************************************** */

// heredoc.c
char	*expand_heredoc(t_shell *shell, char *line, int exp, int quote);
int		handle_heredoc_input(t_shell *shell, char *delimiter, int quoted);
int		setup_heredoc(t_cmd *cmd, char *delimiter, t_shell *shell, int quoted);

// heredoc_utils.c
void	handle_heredoc_signal(int sig);
void	setup_heredoc_signals(void);
void	restore_signals(void);
char	*create_tmp_heredoc_file(void);

// manage_cmd
void	fork_error_handler(t_shell *shell, t_cmd *cmd, int err, int exit_code);
int		is_directory(char *path);
void	execve_failed(t_shell *shell, t_cmd *cmd, char *path);
void	execute_cmd(t_shell *shell, t_cmd *cmd);
void	print_envp_char(char **envp);
void	execute_command_list(t_shell *shell);

// pipeline_utils
int		setup_pipe_fds(t_cmd *current, int prev_pipe, int *fd_pipe);
void	handle_parent_process(t_cmd *current, int prev_pipe, int *fd_pipe);
void	handle_child_process(t_shell *shell, t_cmd *current, int prev_pipe, int *fd_pipe);
void	wait_for_children(t_shell *shell);
int		create_and_fork_process(t_cmd *current, int *fd_pipe);
int		execute_pipeline(t_shell *shell);
void	close_outfile(t_cmd *cmd);

#endif
