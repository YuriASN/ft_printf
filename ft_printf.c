#include "ft_printf.h"

/** @brief
 * Call handler functions of normal flags
 * accordingly to current char after %.
 * If none found, return 0.
 * @param l
 * The list of arguments to be used on flags.
 * @param c
 * The char indicating the current flag.
 * @return
 * Amount of characters put on stdout. */
static int	print_arg(va_list *l, char c)
{
	char	letter;

	if (c == 'c')
	{
		letter = (char)va_arg(*l, int);
		return (write(1, &letter, 1));
	}
	if (c == 's')
		return (ft_putstr_fd(va_arg(*l, char *), 1));
	if (c == 'd' || c == 'i')
		return (f_putnbr(va_arg(*l, int)));
	if (c == 'u')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789", 10));
	if (c == 'x')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789abcdef", 16));
	if (c == 'X')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789ABCDEF", 16));
	if (c == 'p')
		return (f_putnbr_ul(va_arg(*l, unsigned long)));
	if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

/** @brief
 * Write the given sring on stdout, changing it's flags
 * for the value of parameter given.
 * @param str
 * String to be written.
 * @param ...
 * Variable amount of parameters to be used on place of the flags.
 * @return
 * Amount of characters that were written to stdout. */
int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	int		last;
	va_list	l;

	if (!str)
		return (-1);
	i = -1;
	count = 0;
	va_start(l, str);
	while (str[++i])
	{
		if (str[i] == '%')
			last = print_arg(&l, str[++i]);
		else
			last = write(1, &str[i], 1);
		if (last == -1)
			return (-1);
		count += last;
	}
	va_end(l);
	return (count);
}
