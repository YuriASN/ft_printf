#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"

int	ft_printf(const char *str, ...);
int	f_putnbr(int n);
int	base_conversor(ssize_t n, char *str, ssize_t base);
int	f_putnbr_u(unsigned int n, char *str, ssize_t base);
int	f_putnbr_ul(unsigned long n);

#endif
