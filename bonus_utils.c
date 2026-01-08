#include "ft_printf_bonus.h"

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
