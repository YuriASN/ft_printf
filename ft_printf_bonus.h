#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <stdarg.h>
# include "libft/libft.h"

int		ft_printf(const char *str, ...);
int		print_arg(va_list *l, const char *c, int *i);
int		get_digits(ssize_t n);
int		f_putnbr_u(unsigned int n, char *str, ssize_t base);
int		f_putnbr_ul(unsigned long n);
int		justfy_left(va_list *l, const char *s, int *i);
int		justfy_right(va_list *l, const char *s, int *i);
int		digit_amount(va_list *l, const char *s, int *i);
int		base_teller(va_list *l, const char *s, int *i);
int		print_space(va_list *l, const char *s, int *i);
int		print_signal(va_list *l, const char *s, int *i);
void	get_u_long(unsigned long n, char base, char *conv);
void	get_nbr(int n, char base, char *conv, int sign);

#endif
