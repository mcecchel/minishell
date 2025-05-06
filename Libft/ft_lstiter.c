/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:30:52 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/05 11:12:57 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione lstiter itera su ogni elemento di un elenco collegato e applica una
determinata funzione al contenuto di ogni elemento della lista.
La funzione `ft_lstiter` prende due argomenti: lst (puntatore al primo
elemento dell'elenco collegato), e f (puntatore a una funzione che prende come
argomento un puntatore `void`).
------------------------------------------------------------------------------*/
#include "libft.h"

/* static void	toupper_bis(void *content)
{
	char *str;

	str = (char *)content;
	if (str == NULL)
		return ;
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
			*str = *str - 32;
		str++;
	}
} */
void	ft_lstiter(t_lst *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
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
int	main()
{
	t_list	*list = ft_lstnew(strdup("Nodo 1"));
	list->next = ft_lstnew(strdup("Nodo 2"));
	list->next->next = ft_lstnew(strdup("Nodo 3"));

	printf("Contenuto della lista prima dell'iterazione:\n");
	ft_print_list(list);

	ft_lstiter(list, &toupper_bis);
	printf("Contenuto della lista dopo l'iterazione:\n");
	ft_print_list(list);
	ft_lstclear(&list, free);
	return (0);	
} */
