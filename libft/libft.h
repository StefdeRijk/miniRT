#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef union u_modf_union {
	double			f;
	unsigned long	l;
}	t_modf_union;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char*str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *n);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *n);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(ft)(void *), void (*del)(void *));
int		ft_lstsize(t_list *lst);
void	ft_putmem_fd(void *s, size_t n, int fd);
int		ft_isspace(char c);
void	*ft_realloc(void *p, size_t size, size_t old_size);
void	*ft_memdup(const void *m, size_t size);
void	ft_lstremove(t_list **lst, t_list *rem, void (*del)(void *));
void	ft_lstremove_n(t_list **lst, t_list *rem, void (*del)(void *), int n);
void	ft_swap(int *a, int *b);
void	ft_swapf(float *a, float *b);
int		ft_max(int a, int b);
void	ft_lstremove_back(t_list **lst, void (*del)(void *));
int		ft_min(int a, int b);
int		ft_atoi_base(const char *str, int base, char ten);
int		ft_absi(int a);
float	ft_absf(float a);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_print_bits(long a);
double	ft_modf(double a, double *intpart);
int		ft_sign(long a);
int		ft_atoi_skip(char **str);
void	*ft_malloc_or_exit(size_t size);
void	*ft_realloc_or_exit(void *p, size_t size, size_t old_size);

#endif
