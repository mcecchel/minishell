/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:30:08 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/10 14:20:25 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_shell(t_shell *shell, char **envp)
{
    shell->envp = envp;
    shell->cmd = NULL;
    shell->n_cmds = 0;
    shell->in_quote = false;
    shell->token.head = NULL;
    shell->token.current = NULL;
}

void cleanup_shell(t_shell *shell)
{
    if (shell->cmd)
    {
        free_cmd_list(shell->cmd);
        shell->cmd = NULL;
    }
    if (shell->token.head)
    {
        free_tokens(shell->token.head);
        shell->token.head = NULL;
        shell->token.current = NULL;
    }
}

int main(int argc, char **argv, char **envp)
{
    char    *line;
    t_shell shell;
    
    (void)argc;
    (void)argv;
    init_shell(&shell, envp);
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
        {
            printf("\nExiting...\n");
            break;
        }
        // Ignora linee vuote
        if (*line == '\0')
        {
            free(line);
            continue;
        }
        add_history(line);
        // Tokenizza l'input
        if (!tokenize_input(&shell.token, line))
        {
            ft_printf("Error: Tokenization failed\n");
            free(line);
            continue;
        }
        // Debug opzionale
        #ifdef DEBUG
        printf("Generated tokens:\n");
        debug_tokens(shell.token.head);
        #endif
        // Parsing
        shell.cmd = parse_tokens(shell.token.head);
        if (!shell.cmd)
        {
            cleanup_shell(&shell);
            free(line);
            continue;
        }
        // Debug opzionale
        #ifdef DEBUG
        printf("\nGenerated commands:\n");
        debug_cmds(shell.cmd);
        #endif
        execute_command_list(&shell);
        cleanup_shell(&shell);
        free(line);
    }
    cleanup_shell(&shell);
    return (0);
}
