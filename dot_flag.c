#include "ft_printf_bonus.h"

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
	if (is_nbr_flag(*s))
	{
		arg_to_str(l, nbr_c, *s);
		return (add_zeros_nbr(nbr_c, teller, width, *s));
	}
	else if (*s == 's')
		return (put_str_len((char *)va_arg(*l, char *), width));
	return (0);
}
