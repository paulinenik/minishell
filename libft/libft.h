/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:09:03 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/15 15:08:21 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memcpy(void *rest, const void *restsrc, size_t n);
int					ft_atoi(const char *str);
void				*ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strchr(const char *s, int ch);
char				*ft_strdup(const char *c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(char const *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *s1, const char *sub, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim (char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *c);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
int					ft_putchar(int i);
void				ft_putstr(char *s, int *i);
void				ft_putendl(char *s, int *i);
void				ft_putnbr(long int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strcmp(char *s1, char *s2);
int					ft_scmp(const char *s1, const char *s2, char c);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));

#endif
