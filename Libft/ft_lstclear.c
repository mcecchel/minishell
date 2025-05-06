/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:01:18 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/05 11:13:07 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione lstclear libera tutti gli elementi di una lista concatenata, sia i
dati contenuti nei nodi che i nodi stessi. La funzione prende due argomenti: lst
(puntatore al primo elemento dell'elenco), e del (puntatore a funzione usato per
cancellare il contenuto di ogni elemento).
------------------------------------------------------------------------------*/
#include "libft.h"

void	ft_lstclear(t_lst **lst, void (*del)(void*))
{
	t_lst	*tmp;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
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
	t_list	*list = ft_lstnew(strdup("1"));
	list->next = ft_lstnew(strdup("2"));
	list->next->next = ft_lstnew(strdup("3"));
	
	printf("Lista prima di ft_lstdelone:\n");
	ft_print_list(list);
	
	ft_lstclear(&list, free);// A questo punto list è NULL
	printf("Lista dopo ft_lstdelone:\n");
	ft_print_list(list);
	return (0);
} */