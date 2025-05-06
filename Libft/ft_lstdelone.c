/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:35:53 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/05 11:13:02 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione lstdelone elimina un nodo specifico da un elenco collegato,
liberando la memoria allocata per il contenuto del nodo e il nodo stesso. La
funzione accetta due argomenti: lst (puntatore al nodo che deve essere
cancellato), e del (puntatore a una funzione usata per liberare il contenuto
del nodo).
------------------------------------------------------------------------------*/
#include "libft.h"

void	ft_lstdelone(t_lst *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
	lst = NULL;
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
int main()
{
    t_list *nodo1 = ft_lstnew(strdup("Nodo 1"));
    t_list *nodo2 = ft_lstnew(strdup("Nodo 2"));
    t_list *nodo3 = ft_lstnew(strdup("Nodo 3"));
    nodo1->next = nodo2;
    nodo2->next = nodo3;

    printf("Lista prima di ft_lstdelone:\n");
    ft_print_list(nodo1);
	
    ft_lstdelone(nodo2, free);
	nodo1->next = nodo3;
    printf("Lista dopo ft_lstdelone:\n");
    ft_print_list(nodo1);
    ft_lstdelone(nodo1, free);
	ft_lstdelone(nodo3, free);
    return 0;
} */