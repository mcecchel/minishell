/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:19:36 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/05 11:13:11 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione lstadd_front aggiunge un nuovo elemento alla parte anteriore di un
elenco collegato. La funzione accetta due argomenti: lst (puntatore al primo
elemento dell'elenco), e new (puntatore al nuovo elemento da aggiungere).
------------------------------------------------------------------------------*/
#include "libft.h"

void	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	if (lst != NULL && new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

/* static void	ft_print_list(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->content != NULL)
			printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}
int	main()
{
	t_list	*head = NULL;
	t_list	*new_node;
	
	new_node = ft_lstnew("Baudo");
	ft_lstadd_front(&head, new_node);
	new_node = ft_lstnew("Pippo");
	ft_lstadd_front(&head, new_node);
	ft_print_list(head);

	t_list	*temporary;

	while (head != NULL)
	{
		temporary = head;
		head = head->next;
		free(temporary);
	}
	return (0);
} */