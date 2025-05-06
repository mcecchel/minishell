/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:59:10 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/05 11:12:39 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione lstsize calcola il numero di elementi di una lista collegata (: la
lunghezza della lista). La funzione prende un singolo argomento lst (puntatore
al primo elemento (head) di una lista collegata).
- Output: Il numero di nodi nella lista

La funzione restituisce il valore di `count`, che rappresenta il numero totale
di nodi dell'elenco.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_lstsize(t_lst *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count ++;
		lst = lst->next;
	}
	return (count);
}
/* int	main()
{
	t_list nodo1 = {NULL, NULL};
	t_list nodo2 = {"Ciao", &nodo1};
	t_list nodo3 = {"amici", &nodo2};
	t_list nodo4 = {"con", &nodo3};
	t_list nodo5 = {"la", &nodo4};
	t_list nodo6 = {"bici", &nodo5};
	printf("La lista ha %d nodi\n", ft_lstsize(&nodo6));
	return (0);
} */