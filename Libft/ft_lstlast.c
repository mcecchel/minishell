/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:18:45 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/05 11:12:53 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione lstlast trova l'ultimo elemento di un elenco collegato.
La funzione attraversa la lista nodo per nodo, utilizzando il campo next per
passare al nodo successivo, fino a trovare un nodo il cui next è NULL.
- Input: puntatore al primo nodo della lista (head).
- Output: puntatore all'ultimo nodo(dove next=NULL), o NULL se lst è vuota

La funzione restituisce il puntatore all'ultimo elem dell'elenco.
------------------------------------------------------------------------------*/
#include "libft.h"

t_lst	*ft_lstlast(t_lst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/* int	main()
{
	t_list *nodo1 = ft_lstnew("Primo");
	t_list *nodo2 = ft_lstnew("Secondo");
	t_list *nodo3 = ft_lstnew("Ultimo");
	nodo1->next = nodo2;
	nodo2->next = nodo3;
	t_list *last = ft_lstlast(nodo1);

	if (last == NULL)
		printf("La lista è vuota\n");
	else
	{
		printf("L'ultimo nodo è: %s\n", (char *)last->content);
		printf("Next è: %p\n", last->next);
	}
	free(nodo1);
	free(nodo2);
	free(nodo3);
	return (0);
} */