#include "ft_printf_bonus.h"

/** @brief Tells if current 1st char of string is a '0',
 * signalizing a zero flag, or if the previous char is '#',
 * for teller flag.
 * @param s String to search on.
 * @param flag If 0 search for zero flag, if not search for teller.
 * @return 1 if true, 0 if not. */
static int	get_flag(const char *s, int flag)
{
	if (flag == 0)
	{
		if (*s == '0')
			return (1);
		return (0);
	}
	if (s[-1] == '#')
		return (2);
	return (0);
}

/** @brief Get the  arg and  it's width, if it is a number.
 * @param s Current location of the string being written by ft_printf().
 * @param l Lis of args of ft_printf().
 * @param nbr_c String that will buffer the arg.
 * @return Lenght of the arg or 0 if isn't a number.
 */
static int	get_arg_nbr(const char *s, va_list *l, char *nbr_c)
{
	int	arg_width;

	arg_width = 0;
	if (is_nbr_flag(*s) || *s == 'p')
		arg_width = arg_to_str(l, nbr_c, *s);
	return (arg_width);
}

/** @brief Write on stdout zeros followed string, both filling full width.
 * @param nbr_c String to be written.
 * @param teller Tells if need a hex base teller.
 * @param full_width The full width to be filled.
 * @param s Current location of the string being written by ft_printf().
 * @return Amount of chars written or -1 in case of error. */
static int	adding_zero(char *nbr_c, int teller, int full_width, const char *s)
{
	if (nbr_c[0] == '0' && s[-1] == '.' && s[0] == '0' && !ft_isdigit(s[1]))
		return (0);
	if (*nbr_c == '-')
		full_width--;
	return (add_zeros_nbr(nbr_c, teller, full_width, *s));
}

/** @brief Write on stdout spaces followed by the teller in case there's one,
 * both filling full width.
 * @param s Current location of the string being written by printf().
 * @param l List of args of ft_printf().
 * @param space_len The lenght of spaces needed to be written
 * @param teller Flag to know if there's a teller on a hex number.
 * @return Amount of chars written, or -1 in case of error. */
static int	adding_spaces(const char *s, va_list *l, int space_len, int teller)
{
	int		arg_width;
	va_list	cp;

	arg_width = 0;
	if (*s == '%' || *s == 'c')
		arg_width = 1;
	else if (*s == 's')
	{
		va_copy(cp, *l);
		arg_width = ft_strlen((char *)va_arg(cp, char *));
		va_end(cp);
	}
	while (arg_width < space_len)
		if (++arg_width && write(1, " ", 1) == -1)
			return (-1);
	if (teller)
		if (put_teller(*s) == -1)
			return (-1);
	return (0);
}

/* Gives the argument with minimum X amount of CHARS. 
In case the first number is 0 and arg is d or i, it adds
zero to complement, otherwise add spaces. */
int	justify_right(va_list *l, const char *s, int *i)
{
	char	nbr_c[20];
	int		full_width;
	int		arg_width;
	int		teller;
	int		zero_flag;

	teller = get_flag(s, 1);
	zero_flag = get_flag(s, 0);
	full_width = ft_atoi(s);
	ft_bzero(nbr_c, 20);
	jump_digits(&s, i);
	arg_width = get_arg_nbr(s, l, nbr_c);
	if (zero_flag && (is_nbr_flag(*s) || *s == 'p'))
		return (adding_zero(nbr_c, teller, full_width, s));
	else
		if (adding_spaces(s, l, full_width - arg_width, teller) == -1)
			return (-1);
	if (nbr_c[0] && ft_putstr_fd(nbr_c, 1) == -1)
		return (-1);
	if (!nbr_c[0] && print_arg(l, s, i) == -1)
		return (-1);
	if (arg_width >= full_width)
		return (arg_width);
	return (full_width);
}
