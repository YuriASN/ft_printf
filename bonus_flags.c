#include "ft_printf_bonus.h"

/* '-' In combination with a value sets the chars (next if)
after the arg, instead of before */
int	justify_left(va_list *l, const char *s, int *i)
{
	int	width;
	int	j;
	int	flag_teller;

	flag_teller = 0;
	++*i;
	if (s[0] == '.')
		return (print_arg(l, s, i));
	if (s[0] == '#')
	{
		flag_teller = 2;
		++*i;
		++s;
	}
	width = ft_atoi(s);
	jump_digits(&s, i);
	if (flag_teller)
		if (put_teller(*s) == -1)
			return (-1);
	j = print_arg(l, s, i);
	while (j < width - flag_teller)
		if (++j && write(1, " ", 1) == -1)
			return (-1);
	return (j + flag_teller);
}

/** @brief
 * Used with x or X flags, it adds 0x or 0X before the
 * conversion respectively, only if value isn't 0.
 * @param l
 * The list
 * @param s
 * String on the current index
 * @param i
 * Pointer to current index of string
 * @return
 * How many chars where printed, or -1 in case of error. */
int	base_teller(va_list *l, const char *s, int *i)
{
	int				check;
	unsigned int	nbr;

	nbr = 0;
	check = 0;
	(*i)++;
	if (s[0] == 'x' || s[0] == 'X')
	{
		nbr = (va_arg(*l, unsigned int));
		if (nbr <= 0)
			return (write(1, "0", 1));
		if (s[0] == 'x')
			return (f_putnbr_ul((unsigned long)nbr));
		else
		{
			if (write(1, "0X", 2) == -1)
				return (-1);
			check = f_putnbr_u(nbr, "0123456789ABCDEF", 16);
		}
		return (check + 2);
	}
	else
		return (print_arg(l, s, i));
}

/* puts space before a number if isn't negative. Only works with d or i flags */
int	print_space(va_list *l, const char *s, int *i)
{
	ssize_t	nbr;
	int		check;

	(*i)++;
	if (s[0] != 'd' && s[0] != 'i')
		return (print_arg(l, s, i));
	nbr = (ssize_t)va_arg(*l, int);
	if (nbr >= 0)
		if (write(1, " ", 1) == -1)
			return (-1);
	check = ft_putnbr_fd(nbr, 1);
	if (check == -1)
		return (-1);
	if (nbr >= 0)
		return (check + 1);
	return (check);
}

/* puts a '+' before a number if isn't negative. Only works with d or i flags */
int	print_signal(va_list *l, const char *s, int *i)
{
	int	nbr;
	int	check;

	(*i)++;
	if (s[0] != 'd' && s[0] != 'i')
		return (print_arg(l, s, i));
	nbr = va_arg(*l, int);
	if (nbr >= 0)
		if (write(1, "+", 1) == -1)
			return (-1);
	check = ft_putnbr_fd(nbr, 1);
	if (check == -1)
		return (-1);
	if (nbr >= 0)
		return (check + 1);
	return (check);
}
