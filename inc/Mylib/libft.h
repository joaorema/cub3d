/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:55:51 by jpedro-c          #+#    #+#             */
/*   Updated: 2025/06/26 19:26:29 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define MAX_FD 1024

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_gnllist
{
	char				*str_buff;
	struct s_gnllist	*next;
}	t_gnllist;

t_list		*ft_listnew(void *content);
t_gnllist	*find_last_node(t_gnllist *list);
t_gnllist	**get_gnl_list(void);

void		ft_bzero(void *s, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_dealloc(t_gnllist **list, t_gnllist *clean_node, char *buffer);
void		ft_new_list(t_gnllist **list, int fd);
void		ft_put_buffer_in_list(t_gnllist **list, char *buffer);
void		ft_polish_list(t_gnllist **list);
void		ft_listadd_front(t_list **lst, t_list *new);
void		*safe_free(void *ptr);
void		ft_free_array(void **array);
void		ft_copy_str(t_gnllist *list, char *str);
void		gnl_free_fd(int fd);
void		ft_clear_list(t_gnllist **list);

int			ft_atoi(const char *nptr);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_printx(char type, unsigned long n, int base);
int			ft_prints(char *str);
int			ft_printf(const char *type, ...);
int			ft_printc(int c);
int			ft_printd(int n);
int			ft_printu(unsigned int n);
int			ft_printp(unsigned long pointer);
int			ft_listsize(t_list *lst);
int			space(int c);
int			str_size(char *str, char end);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_newline(t_gnllist *list);
int			len_new_line(t_gnllist *list);

size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *s);
size_t		ft_strnlen(const char *s, size_t maxlen);

char		*ft_strchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strndup(const char *src, size_t n);
char		*ft_strcpy(char *dest, const char *src);
char		ft_is_numeric(const char *str);
char		*get_next_line(int fd);
char		*ft_get_line(t_gnllist *list);

long		ft_atol(const char *nptr);

#endif
