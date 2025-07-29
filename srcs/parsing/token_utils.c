/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:57:03 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 16:00:36 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	classify_token(char *str, int is_first_token, int is_quoted)
{
	if (!str)
		return (UNKNOWN);
	if (is_quoted)
	{
		if (is_first_token)
			return (CMD);
		else
			return (ARG);
	}
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	if (ft_strcmp(str, ">") == 0)
		return (RED_OUT);
	if (ft_strcmp(str, "<") == 0)
		return (RED_IN);
	if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	if (is_first_token)
		return (CMD);
	if (str[0] == '-' && str[1] != '\0')
		return (FLAG);
	return (ARG);
}

t_token	*create_token(char *content, t_token_type type, int is_quoted)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = content;
	new_token->type = type;
	new_token->is_quoted = is_quoted;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token *token_list, t_token *new_token)
{
	if (!token_list->head)
	{
		token_list->head = new_token;
		token_list->current = new_token;
	}
	else
	{
		token_list->current->next = new_token;
		token_list->current = new_token;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

t_token	*ft_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
