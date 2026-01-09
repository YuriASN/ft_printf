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
void	get_unsig(unsigned int n, char base, char *conv);
void	get_unsig_long(unsigned long n, char *conv);
void	get_nbr(ssize_t n, char *conv, int sign);
int		put_teller(char c);
void	jump_digits(const char **str, int	*i);
int		arg_to_str(va_list *l, char *str, char type);
int		add_zeros_nbr(char *nbr_c, int teller, int full_width, char current);

#endif
