/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:24:05 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/01 15:10:56 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

// # include "ft_printf.h"
// # include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// lib/Libft/ft_is
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

// lib/Libft/ft_list
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// lib/Libft/ft_memory
void	*ft_bzero(void *str, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const char *str1, const char *str2, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *ptr, size_t size);
void	*ft_recalloc(void *ptr, size_t size, size_t old_size);
void	ft_free2d(char **memory);
void	ft_free_safe(void **memory);
void	ft_free2d_safe(char ***memory);

// lib/Libft/ft_put_fd
void	ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(const char *s, const int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// lib/Libft/ft_string
size_t	ft_strlen(const char *str);
size_t	ft_strlen2(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t dsize);
size_t	ft_strlcpy2(char *dest, const char *src, size_t dsize);
size_t	ft_strlcat(char *dest, const char *src, size_t dsize);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t look);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strdup(const char *s1);

// lib/Libft/ft_to
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_toupper(int c);
int		ft_tolower(int c);

#endif
