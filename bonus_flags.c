#include "ft_printf_bonus.h"

/* '-' In combination with a value sets the chars (next if)
after the arg, instead of before */
int	justfy_left(va_list *l, const char *s, int *i)
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


/* Gives the argument with minimum X amount of CHARS. 
In case the first number is 0 and arg is d or i, it adds
zero to complement, otherwise add spaces. */
int	justfy_right(va_list *l, const char *s, int *i)
{
	char	nbr_c[20];
	int		full_width;
	int		arg_width;
	int		teller;
	int		zero_flag;
	va_list	cp;

	teller = 0;
	zero_flag = 0;
	arg_width = 0;
	full_width = ft_atoi(s);
	ft_bzero(nbr_c, 20);
	if (s[-1] == '#')
		teller = 2;
	if (*s == '0')
		zero_flag++;
	jump_digits(&s, i);
	if (*s == 'd' || *s == 'i' || *s == 'u'
		|| *s == 'x' || *s == 'X' || *s == 'p')
		arg_width = arg_to_str(l, nbr_c, *s);
	if (zero_flag && (*s == 'd' || *s == 'i' || *s == 'u'
			|| *s == 'x' || *s == 'X' || *s == 'p'))
	{
		if (nbr_c[0] == '0' && s[-1] == '.' && s[0] == '0' && !ft_isdigit(s[1]))
			return (0);
		if (*nbr_c == '-')
			full_width--;
		return (add_zeros_nbr(nbr_c, teller, full_width, *s));
	}
	else
	{
		if (*s == '%' || *s == 'c')
			arg_width = 1;
		else if (*s == 's')
		{
			va_copy(cp, *l);
			arg_width = ft_strlen(va_arg(cp, char *));
			va_end(cp);
		}
		while (arg_width < full_width)
			if (++arg_width && write(1, " ", 1) == -1)
				return (-1);
		if (teller)
			if (put_teller(*s) == -1)
				return (-1);
	}
	if (nbr_c[0] && ft_putstr_fd(nbr_c, 1) == -1)
		return (-1);
	if (!nbr_c[0] && print_arg(l, s, i) == -1)
		return (-1);
	if (arg_width >= full_width)
		return (arg_width);
	return (full_width);
}

/** @brief
 * Write on stdout the string up to len chars, or end of string.
 * @param str String to write.
 * @param len Max amount of chars to be written.
 * @return Amount written or -1 if error. */
static int	put_str_len(char *str, int len)
{
	int	i;
	int	str_len;

	i = -1;
	str_len = ft_strlen(str);
	while (++i < len && i < str_len)
		if (write(1, &str[i], 1) == -1)
			return (-1);
	return (i);
}

/* '.' Gives the number with minimum X amount of DIGITS.
Adding zeros before the number it self.
Only works with numbers */
int	digit_amount(va_list *l, const char *s, int *i)
{
	char	nbr_c[20];
	int		width;
	int		teller;

	teller = 0;
	ft_bzero(nbr_c, 20);
	(*i)++;
	if (s[-2] == '#')
		teller = 2;
	width = ft_atoi(s);
	jump_digits(&s, i);
	if (!width)
		return (0);
	if (*s == 'i' || *s == 'd' || *s == 'u'
		|| *s == 'x' || *s == 'X')
	{
		arg_to_str(l, nbr_c, *s);
		return (add_zeros_nbr(nbr_c, teller, width, *s));
	}
	else if (*s == 's')
		return (put_str_len((char *)va_arg(*l, char *), width));
	return (0);
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
