#include "ft_printf_bonus.h"

/** @brief
 * Call handler functions of bonus flags
 * accordingly to current char after %.
 * @param l
 * The list of arguments to be used on flags.
 * @param c
 * The string at the index of current flag.
 * @param i
 * Pointer with value of current index of previous parameter.
 * @return
 * Amount of characters put on stdout. */
static int	print_bonus_arg(va_list *l, const char *c, int *i)
{
	if (c[0] == '-')
		return (justify_left(l, &c[1], i));
	if (ft_isdigit(c[0]))
		return (justify_right(l, c, i));
	if (c[0] == '.')
		return (digit_amount(l, &c[1], i));
	if (c[0] == '#')
		return (base_teller(l, &c[1], i));
	if (c[0] == ' ')
		return (print_space(l, &c[1], i));
	if (c[0] == '+')
		return (print_signal(l, &c[1], i));
	return (write(1, "", 0));
}

/** @brief
 * Call handler functions of normal flags
 * accordingly to current char after %.
 * If none found, call handler for bonus.
 * @param l
 * The list of arguments to be used on flags.
 * @param c
 * The string at the index of current flag.
 * @param i
 * Pointer with value of current index of previous parameter.
 * @return
 * Amount of characters put on stdout. */
int	print_arg(va_list *l, const char *c, int *i)
{
	char	letter;

	if (c[0] == 'c')
	{
		letter = (char)va_arg(*l, int);
		return (write(1, &letter, 1));
	}
	if (c[0] == 's')
		return (ft_putstr_fd(va_arg(*l, char *), 1));
	if (c[0] == 'd' || c[0] == 'i')
		return (ft_putnbr_fd((ssize_t)(va_arg(*l, int)), 1));
	if (c[0] == 'u')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789", 10));
	if (c[0] == 'x')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789abcdef", 16));
	if (c[0] == 'X')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789ABCDEF", 16));
	if (c[0] == 'p')
		return (f_putnbr_ul(va_arg(*l, unsigned long)));
	if (c[0] == '%')
		return (write(1, "%", 1));
	return (print_bonus_arg(l, c, i));
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
			last = print_arg(&l, &str[++i], &i);
		else
			last = write(1, &str[i], 1);
		if (last == -1)
			return (-1);
		count += last;
	}
	va_end(l);
	return (count);
}
