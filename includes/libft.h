/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 11:53:06 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/02 13:50:23 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>

# define BUFF_SIZE 1024

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_gnl
{
	int				fd;
	char			*current_line;
	char			*file;
	struct s_gnl	*next;
}					t_gnl;

typedef char		t_utf8;

/*
** wchar/utf-8 related functions
*/

wchar_t				*ft_wstrndup(const wchar_t *str, size_t n);
wchar_t				*ft_wstrdup(wchar_t *str);
void				*ft_wchar_memset(void *b, wchar_t c, size_t len);
wchar_t				*ft_wstrcpy(wchar_t *dst, wchar_t const *src);
size_t				ft_wstrlen(wchar_t const *str);
size_t				ft_wcharbits(wchar_t c);
size_t				ft_wcharsize_utf8(wchar_t c);
size_t				ft_wstrsize_utf8(const wchar_t *wstr);
size_t				ft_wstrnsize_utf8(const wchar_t *wstr, size_t n);
wchar_t				ft_utf8charencode(wchar_t c);
size_t				ft_utf8charsize(wchar_t c);
int					ft_wctomb(char *s, wchar_t wc);
t_utf8				*ft_utf8strnencode(const wchar_t *wstr, size_t n);
t_utf8				*ft_utf8strencode(const wchar_t *wstr);

char				*ft_itoa_base_ull(unsigned long long value, int base);
int					ft_ishex(size_t c);
char				*ft_itoa_base_uintmax(uintmax_t value, int base);
char				*ft_itoa_base_intmax(intmax_t value, int base);
void				ft_putnbr_llong(long long n);
char				*ft_toupper_str(char *str);
char				*ft_tolower_str(char *str);
char				*ft_itoa_base(int value, int base);
size_t				ft_nbrlen(int nbr);
int					get_next_line(int const fd, char **line);
void				*ft_realloc(void *ptr, size_t size_original,
						size_t size_add);
int					ft_atoi(char const *str);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(size_t c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, void const *src, size_t n);
void				*ft_memccpy(void *dst, void const *src, int c, size_t n);
void				*ft_memmove(void *dst, void const *src, size_t len);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
int					ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_strclr(char *s);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
char				*ft_strcat(char *s1, char const *s2);
char				*ft_strncat(char *s1, char const *s2, size_t n);
size_t				ft_strlcat(char *dst, char const *src, size_t size);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
char				*ft_strcpy(char *dst, char const *src);
void				ft_strdel(char **as);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
size_t				ft_strlen(char const *str);
char				*ft_strdup(char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strncpy(char *dst, char const *src, size_t len);
char				*ft_strndup(const char *str, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(char *str, char *to_find);
char				*ft_strnstr(char const *str, char const *to_find,
						size_t len);
char				**ft_strsplit(char const *s, char c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_wrdcnt(char *s);
int					ft_wrdcntd(char *str, char delimiter);
int					ft_wrdlen(char *str, char delimiter);
char				**ft_wrdsplit(char const *s);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
#endif
