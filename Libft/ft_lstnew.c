/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:54:59 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/05 11:12:45 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione lstnew crea un nuovo nodo per un elenco collegato. La funzione
accetta un singolo argomento `content`, che è un puntatore al contenuto che sarà
memorizzato nel nuovo nodo.

La funzione restituisce il puntatore al nuovo nodo creato.
------------------------------------------------------------------------------*/
#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*new_node;

	new_node = (t_lst *)malloc(sizeof(t_lst));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/* int	main()
{
	char *str = "Mi fa male la testa";
	t_list	*node = ft_lstnew((void *)str);
	if (node == NULL)
	{
		printf("Errore nell'allocazione della memoria\n");
		return (1);
	}
	else
	{
		printf("Il nodo è: %s\n", (char *)node->content);
		printf("Next è: %p\n", node->next);
	}
	free(node);
	return (0);
} */