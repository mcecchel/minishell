/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:02:45 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/06 18:04:35 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

// usare enum perche' cosi' non c'e' bisogno di specificare il tipo delle variabili
typedef enum e_token
{
// Parole
	cmd,
	arg,
	option,
	flag,
// Operatori di controllo
	pipe,
// Operatori di redirezione
	red_in,
	red_out,
	red_append,
	red_heredoc,
// Parentesi e simboli speciali
	quote,
	dquote,
	space_in_quote,
	unknown,
}			t_token;

typedef struct s_all
{
	t_token		token;

}				t_all;

# endif