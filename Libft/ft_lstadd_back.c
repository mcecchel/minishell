/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:12:06 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/05 11:13:17 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione lstadd_back aggiunge un nuovo elemento alla fine di un elenco
collegato. Attraversa la lista nodo per nodo, utilizzando  next per passare al
nodo successivo fino a trovare un nodo il cui (next = NULL).
La funzione prende due argomenti: lst (puntatore al primo elemento dell'elenco),
e new (puntatore al nuovo elemento da aggiungere).
------------------------------------------------------------------------------*/
#include "libft.h"

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
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
	t_list	*list = NULL;
	t_list *nodo1 = ft_lstnew("Ciao");
	t_list *nodo2 = ft_lstnew("bella");
	t_list *nodo3 = ft_lstnew("gente");
	ft_lstadd_back(&list, nodo1);//aggiunge i nodi 1-2-3 alla lista
	ft_lstadd_back(&list, nodo2);
	ft_lstadd_back(&list, nodo3);
	ft_print_list(list);
	
	t_list	*temporary;
	while (list != NULL)
	{
		temporary = list;
		list = list->next;
		free(temporary);
	}
	return (0);
} */
