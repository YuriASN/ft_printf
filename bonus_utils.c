#include "ft_printf_bonus.h"

/** @brief 
 * Returns true or false if the flag given is a flag for numbers.
 * Covers the bases d, i, u, x or X.
 * @param c Character to chek the flag.
 * @return 1 if true, 0 if not. */
int	is_nbr_flag(char c)
{
	if (c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X')
		return (1);
	return (0);
}

/** @brief
 * Writes to std out the given teller of base x, p or X.
 * @param base Base to be explicited on stdout.
 * @return Amount of chars written or -1 if error. */
int	put_teller(char c)
{
	if (c == 'x' || c == 'p')
		return (write(1, "0x", 2) == -1);
	if (c == 'X')
		return (write(1, "0X", 2) == -1);
	return (0);
}

/** @brief Passes all firsts digits from the string
 * and add it's index the same amount.
 * @param str Pointer to string to pass first digits.
 * @param i Pointer to current index of it. */
void	jump_digits(const char **str, int	*i)
{
	while (ft_isdigit(**str))
	{
		++*i;
		(*str)++;
	}
}

/** @brief Read an arg that should be a number to a string.
 * @param l List with the arg to pass.
 * @param str String to receive numbers of arg
 * @param type Type of arg it is.
 * @return Amount of digits written on str. */
int	arg_to_str(va_list *l, char *str, char type)
{
	if (type == 'X' || type == 'x')
		get_unsig(va_arg(*l, unsigned int), type, str);
	else if (type == 'u')
		get_unsig(va_arg(*l, unsigned int), '0', str);
	else if (type == 'p')
		get_unsig_long(va_arg(*l, unsigned long), str);
	else if (type == 'd' || type == 'i')
		get_nbr((ssize_t)va_arg(*l, int), str, 1);
	if (type == 'p')
	{
		if (*str == '0')
			ft_strlcpy(str, "(nil)\0", 6);
		else
		{
			ft_memmove(&str[2], str, ft_strlen(str));
			str[0] = '0';
			str[1] = 'x';
		}
	}
	return (ft_strlen(str));
}

/** @brief
 * Writes to stdout the amount of zeros needed
 * to set arg to the asked minimum width.
 * @param nbr_c
 * The arg to be printed. A number on a sstring.
 * @param teller
 * Tells if the base x or X will be displayed before the arg.
 * @param width
 * The Minimum width to be written.
 * @return
 * The amount of chars written or -1 if error occurs. */
int	add_zeros_nbr(char *nbr_c, int teller, int full_width, char current)
{
	int	arg_width;

	arg_width = ft_strlen(nbr_c);
	if (teller)
		if (put_teller(current) == -1)
			return (-1);
	if (!teller && *nbr_c == '-')
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		ft_memmove(nbr_c, &nbr_c[1], 20);
		full_width++;
	}
	if (nbr_c[1] == 'x' || nbr_c[1] == 'X')
	{
		if (write(1, nbr_c, 2) == -1)
			return (-1);
		nbr_c += 2;
	}
	while (arg_width < full_width)
		if (++arg_width && write(1, "0", 1) == -1)
			return (-1);
	if (write(1, nbr_c, ft_strlen(nbr_c)) == -1)
		return (-1);
	return (arg_width + teller);
}
