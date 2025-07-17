/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:25:56 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/17 18:04:40 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# ifndef DEBUG
#  define DEBUG 1
# endif

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>

typedef enum e_what
{
	EMPTY,
	ALPHA,
	NUM,
	ALPHANUM,
	ALL,
	OTHERS,

}			t_what;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		is_space(char c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		what_is(char *str, int n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putchar(char c);

size_t	ft_strlen(const char *s);
int		ft_counter(int nbr);

// Bonus part
typedef struct a_list
{
	void			*content;
	struct a_list	*next;
}					t_lst;

t_lst	*ft_lstnew(void *content);
void	ft_lstadd_front(t_lst **lst, t_lst *new);
int		ft_lstsize(t_lst *lst);
t_lst	*ft_lstlast(t_lst *lst);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
void	ft_lstdelone(t_lst *lst, void (*del)(void*));
void	ft_lstclear(t_lst **lst, void (*del)(void*));
void	ft_lstiter(t_lst *lst, void (*f)(void *));

// ft_printf functions
int		ft_counter(int nbr);
int		ft_hex_counter(unsigned int nbr);
int		ft_putchar_pf(int fd, char c);
int		ft_putstr_pf(int fd, char *str);
int		ft_percent_fd(int fd);
int		ft_putdecimal_fd(int fd, int nbr);
int		ft_putunsign(int fd, unsigned int nbr);
int		ft_puthexamin(int fd, unsigned int nbr);
int		ft_puthexamai(int fd, unsigned int nbr);
int		ft_putptr(int fd, void *ptr);
int		ft_printf(const char *str, ...);
int		printf_debug(const char *str, ...);
int		fd_printf(int fd, const char *str, ...);


// get_next_line functions
char	*get_next_line(int fd);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strjoin_gnl(char *s1, char *s2);

#endif
