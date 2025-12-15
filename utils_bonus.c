#include "ft_printf_bonus.h"

/* '-' In combination with a value sets the chars (next if)
after the arg, instead of before */
int	justfy_left(va_list *l, const char *s, int *i)
{
	int	width;
	int	j;

	++*i;
	if (s[0] == '.')
		return (print_arg(l, s, i));
	if (ft_isdigit(s[0]))
		width = ft_atoi(s);
	j = -1;
	while (ft_isdigit(s[++j]))
		++*i;
	j = print_arg(l, &s[j], i);
	while (j++ < width)
		if (write(1, " ", 1) == -1)
			return (-1);
	return (j - 1);
}


/* Gives the argument with minimum X amount of CHARS. 
In case the first number is 0 and arg is d or i, it adds
zero to complement, otherwise add spaces. */
int	justfy_right(va_list *l, const char *s, int *i)
{
	char	nbr_c[20];
	int		full_width;
	int		arg_width;
	int		j;
	va_list	cp;

	full_width = ft_atoi(s);
	j = -1;
	ft_bzero(nbr_c, 20);
	while (ft_isdigit(s[++j]))
		++*i;
	if (s[j] == 'X')
		get_u_long(va_arg(*l, unsigned long), 'X', nbr_c);
	else if (s[j] == 'x' || s[j] == 'p')
		get_u_long(va_arg(*l, unsigned long), 'x', nbr_c);
	else if (s[j] == 'u')
		get_u_long(va_arg(*l, unsigned long), '0', nbr_c);
	else if (s[j] == 'd' || s[j] == 'i')
		get_nbr(va_arg(*l, int), '0', nbr_c, 1);
//if it's number or hex	|0x0000007ffdd8952118| and flag 0, add 0
	if (s[0] == '0' && (s[j] == 'd' || s[j] == 'i' || s[j] == 'u'
			|| s[j] == 'x' || s[j] == 'X' || s[j] == 'p'))
	{
		//if value after . is 0 only and number is 0 = writes nothing
		if (nbr_c[0] == '0' && s[-1] == '.' && s[0] == '0' && !ft_isdigit(s[1]))
			return (0);
		arg_width = ft_strlen(nbr_c);
		if (s[j] == 'p')
		{
			arg_width += 2;
			if (write(1, "0x", 2) == -1)
				return (-1);
		}
		while (arg_width++ < full_width)
			if (write(1, "0", 1) == -1)
				return (-1);
	}
	else			//will add spaces
	{
		if (s[j] == '%' || s[j] == 'c')
			arg_width = 1;
		else if (s[j] == 's')
		{
			va_copy(cp, *l);
			arg_width = ft_strlen(va_arg(cp, char *));
			va_end(cp);
		}
		else if (s[j] == 'd' || s[j] == 'i' || s[j] == 'u'
			|| s[j] == 'x' || s[j] == 'X' || s[j] == 'p')
			arg_width = ft_strlen(nbr_c);
		while (arg_width++ < full_width)
			if (write(1, " ", 1) == -1)
				return (-1);
	}
	if (nbr_c[0] && ft_putstr_fd(nbr_c, 1) == -1)
		return (-1);
	if (!nbr_c[0] && print_arg(l, &s[j], i) == -1)
		return (-1);
	return (full_width);
}

/* '.' Gives the number with minimum X amount of DIGITS.
Adding zeros before the number it self.
Only works with numbers */
int	digit_amount(va_list *l, const char *s, int *i)
{
	char	nbr_c[20];
	int		width;
	int		j;

	(*i)++;
	if (ft_isdigit(s[0]))
		width = ft_atoi(s);
	j = -1;
	while (ft_isdigit(s[++j]))
		(*i)++;
	ft_bzero(nbr_c, 20);
	if (s[j] == 'i' || s[j] == 'd' || s[j] == 'u'
		|| s[j] == 'x' || s[j] == 'X')
	{
		if (s[j] == 'X')
			get_u_long(va_arg(*l, unsigned long), 'X', nbr_c);
		else if (s[j] == 'x' || s[j] == 'p')
			get_u_long(va_arg(*l, unsigned long), 'x', nbr_c);
		else if (s[j] == 'u')
			get_u_long(va_arg(*l, unsigned long), '0', nbr_c);
		else if (s[j] == 'd' || s[j] == 'i')
			get_nbr(va_arg(*l, int), '0', nbr_c, 1);
		j = ft_strlen(nbr_c);
		while (j++ < width)
			if (write(1, "0", 1) == -1)
				return (-1);
		if (write(1, nbr_c, ft_strlen(nbr_c)) == -1)
			return (-1);
	}
	return (width);
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
	int	check;

	(*i)++;
	if (s[0] == 'x')
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		check = f_putnbr_u(va_arg(*l, unsigned int), "0123456789abcdef", 16);
		if (check == -1)
			return (-1);
		return (check + 2);
	}
	else if (s[0] == 'X')
	{
		if (write(1, "0X", 2) == -1)
			return (-1);
		check = f_putnbr_u(va_arg(*l, unsigned int),
				"0123456789ABCDEF", 16) + 2;
		if (check == -1)
			return (-1);
		return (check + 2);
	}
	else
		return (print_arg(l, s, i));
}

/* puts space before a number if isn't negative. Only works with d or i flags */
int	print_space(va_list *l, const char *s, int *i)
{
	int	nbr;
	int	check;

	(*i)++;
	if (s[0] != 'd' && s[0] != 'i')
		return (print_arg(l, s, i));
	nbr = va_arg(*l, int);
	if (nbr >= 0)
		write(1, " ", 1);
	check = ft_putnbr_fd(nbr, 1);
	if (check == -1)
		return (-1);
	return (check + 1);
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
		write(1, "+", 1);
	check = ft_putnbr_fd(nbr, 1);
	if (check == -1)
		return (-1);
	return (check + 1);
}
