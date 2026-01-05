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
	j = -1;
	while (ft_isdigit(s[++j]))
		++*i;
	if (flag_teller && s[j] == 'x')
		if (write(1, "0x", 2) == -1)
			return (-1);
	if (flag_teller && s[j] == 'X')
		if (write(1, "0X", 2) == -1)
			return (-1);
	j = print_arg(l, &s[j], i);
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
	while (ft_isdigit(*s))
	{
		++*i;
		++s;
	}
	if (*s == 'p')
		teller = 2;
	if (*s == 'X' || *s == 'x')
		get_unsig(va_arg(*l, unsigned int), *s, nbr_c);
	else if (*s == 'u')
		get_unsig(va_arg(*l, unsigned int), '0', nbr_c);
	else if (*s == 'p')
		get_unsig_long(va_arg(*l, unsigned long), nbr_c);
	else if (*s == 'd' || *s == 'i')
		get_nbr((ssize_t)va_arg(*l, int), nbr_c, 1);
//if it's number or hex	|0x0000007ffdd8952118| and flag 0, add 0
	if (zero_flag && (*s == 'd' || *s == 'i' || *s == 'u'
			|| *s == 'x' || *s == 'X' || *s == 'p'))
	{
		//if value after . is 0 only and number is 0 = writes nothing
		if (nbr_c[0] == '0' && s[-1] == '.' && s[0] == '0' && !ft_isdigit(s[1]))
			return (0);
		arg_width = ft_strlen(nbr_c);
		if (*nbr_c == '-')
		{
			write(1, "-", 1);
			ft_memmove(nbr_c, &nbr_c[1], arg_width);
		}
		if (*s == 'p' || (teller && *s == 'x'))
			if (write(1, "0x", 2) == -1)
				return (-1);
		if (teller && *s == 'X')
			if (write(1, "0X", 2) == -1)
				return (-1);
		while (arg_width + teller < full_width)
			if (++arg_width && write(1, "0", 1) == -1)
				return (-1);
	}
	else			//will add spaces
	{
		if (*s == '%' || *s == 'c')
			arg_width = 1;
		else if (*s == 's')
		{
			va_copy(cp, *l);
			arg_width = ft_strlen(va_arg(cp, char *));
			va_end(cp);
		}
		else if (*s == 'd' || *s == 'i' || *s == 'u'
			|| *s == 'x' || *s == 'X' || *s == 'p')
			arg_width = ft_strlen(nbr_c);
		while (arg_width < full_width - teller)
			if (++arg_width && write(1, " ", 1) == -1)
				return (-1);
		if ((teller && *s == 'x') || *s == 'p')
			if (write(1, "0x", 2) == -1)
				return (-1);
		if (teller && *s == 'X')
			if (write(1, "0X", 2) == -1)
				return (-1);
	}
	if (nbr_c[0] && ft_putstr_fd(nbr_c, 1) == -1)
		return (-1);
	if (!nbr_c[0] && print_arg(l, s, i) == -1)
		return (-1);
	if (arg_width + teller >= full_width)
		return (arg_width + teller);
	return (full_width);
}

/* '.' Gives the number with minimum X amount of DIGITS.
Adding zeros before the number it self.
Only works with numbers */
int	digit_amount(va_list *l, const char *s, int *i)
{
	char	nbr_c[20];
	char	*str;
	int		width;
	int		j;
	int		teller;

	teller = 0;
	ft_bzero(nbr_c, 20);
	(*i)++;
	if (s[-2] == '#')
		teller = 2;
	width = ft_atoi(s);
	j = 0;
	while (ft_isdigit(s[j]))
	{
		(*i)++;
		++j;
	}
	if (!width)
		return (0);
	if (s[j] == 'i' || s[j] == 'd' || s[j] == 'u'
		|| s[j] == 'x' || s[j] == 'X')
	{
		if (s[j] == 'X' || s[j] == 'x')
			get_unsig(va_arg(*l, unsigned int), s[j], nbr_c);
		else if (s[j] == 'u')
			get_unsig(va_arg(*l, unsigned int), '0', nbr_c);
		else if (s[j] == 'p')
			get_unsig_long(va_arg(*l, unsigned long), nbr_c);
		else if (s[j] == 'd' || s[j] == 'i')
			get_nbr((ssize_t)va_arg(*l, int), nbr_c, 1);
		j = ft_strlen(nbr_c);
		if (teller && s[j] == 'x')
		{
			if (write(1, "0x", 2) == -1)
				return (-1);
		}
		else if (teller && s[j] == 'X')
		{
			if (write(1, "0X", 2) == -1)
				return (-1);
		}
		else if (*nbr_c == '-')
		{
			write(1, "-", 1);
			ft_memmove(nbr_c, &nbr_c[1], 20);
			width++;
		}
		while (j < width)
			if (++j && write(1, "0", 1) == -1)
				return (-1);
		if (write(1, nbr_c, ft_strlen(nbr_c)) == -1)
			return (-1);
	}
	else if (s[j] == 's')
	{
		str = (char *)va_arg(*l, char *);
		j = 0;
		while (j < width && j < ft_strlen(str))
			if (++j && write(1, &str[j - 1], 1) == -1)
				return (-1);
	}
	else
		return (0);
/*	if (j >= width)
		return (j); */
	return (j + teller);
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
	unsigned long	nbr;
	va_list			cp;

	nbr = 0;
	(*i)++;
	va_copy(cp, *l);
	nbr = (va_arg(cp, unsigned long));
	va_end(cp);
	if (nbr == 0)
		return (write(1, "0", 1));
	if (s[0] == 'x')
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		check = f_putnbr_u(va_arg(*l, unsigned long), "0123456789abcdef", 16);
		if (check == -1)
			return (-1);
		return (check + 2);
	}
	else if (s[0] == 'X')
	{
		if (write(1, "0X", 2) == -1)
			return (-1);
		check = f_putnbr_u(va_arg(*l, unsigned long), "0123456789ABCDEF", 16);
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
