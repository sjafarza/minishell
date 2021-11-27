/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:14:23 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 14:08:16 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

/*
** part1
*/

void			*ft_memset(void *memory_space, int value, size_t len);
void			ft_bzero(void *memory_space, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t len);
void			*ft_memccpy(void *dst, const void *src, int c, size_t len);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t len);
int				ft_memcmp(const void *s1, const void *s2, size_t len);
size_t			ft_strlen(const char *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t len_mx);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *src);

/*
** part2
*/

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
** bonus
*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

/*
** added
*/

void			ft_lstiter_fun_first(t_list *lst, void (*f)(void *));
t_list			*ft_lst_get_elem_by_nb(t_list *lst, int nb);
void			free_array(char **array);
t_list			*ft_lstcut_next(t_list *lst);
int				ft_lstreset(t_list *head_src, t_list *head_dst,
					void *(*copy_content)(void*, void*));
int				ft_lstcpy(t_list *head_src, t_list **head_dst,
					void *(*copy_create_content)(void*));

typedef struct s_list_double
{
	void					*content;
	struct s_list_double	*next;
	struct s_list_double	*prev;
}				t_list_double;

t_list_double	*ft_lstdb_get_elem_by_nb_from_back(t_list_double *lst, int nb);
t_list_double	*ft_lstdb_get_elem_by_nb(t_list_double *lst, int nb);
void			ft_lstdbadd_back(t_list_double **alst, t_list_double *new);
void			ft_lstdbadd_front(t_list_double **alst, t_list_double *new);
void			ft_lstdbclear(t_list_double **lst, void (*del)(void*));
int				ft_lstdbcpy(t_list_double *head_src, t_list_double **head_dst,
					void *(*copy_create_content)(void*));
t_list_double	*ft_lstdbcut(t_list_double *lst);
void			ft_lstdbdelone(t_list_double *lst, void (*del)(void*));
void			ft_lstdbiter_from_back(t_list_double *lst, void (*f)(void *));
void			ft_lstdbiter_fun_first_from_back(t_list_double *lst,
					void (*f)(void *));
void			ft_lstdbiter_fun_first(t_list_double *lst, void (*f)(void *));
void			ft_lstdbiter(t_list_double *lst, void (*f)(void *));
t_list_double	*ft_lstdblast(t_list_double *lst);
t_list_double	*ft_lstdbmap(t_list_double *lst, void *(*f)(void *),
					void (*del)(void *));
t_list_double	*ft_lstdbnew(void *content);
int				ft_lstdbreset(t_list_double *head_src, t_list_double *head_dst,
					void *(*copy_content)(void*, void*));
int				ft_lstdbsize(t_list_double *lst);
int				ft_lstdbfind(t_list_double *head_src, t_list_double **found,
					void *seek, int (*find)(void*, void*));
int				ft_lstdbfind_best_match(t_list_double *head_src,
					t_list_double **found, void *seek,
					int (*find)(void*, void*));
int				ft_lstdbfind_index(t_list_double *head_src, void *seek,
					int (*find)(void*, void*));
int				ft_lstdbcount(t_list_double *head_src, void *target_util,
					int (*is_target)(void*, void*));
t_list_double	*ft_lstdbcut_next(t_list_double *lst);

#endif
