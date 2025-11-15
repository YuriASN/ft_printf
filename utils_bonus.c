#include "ft_printf_bonus.h"

/* In combination with a value sets the chars (next if) after the arg, instead of before */
int	justfy_left(va_list *l, char *s, int *i)
{
	++*i;
	if (s[0] == '.')
		return (print_arg(l, s, i));
	
}

/* Gives the argument with minimum X amount of CHARS. 
In case the first number is 0 and arg is d or i, it adds zero to complement, otherwise add spaces. */
int	right_width(va_list *l, char *s, int *i)
{
	int	nbr;

	nbr = va_arg(*l, int);
	if (s[0] == 0 && s[-1] != '-')	//will add zeros
	{

	}
	else			//will add spaces
	{
		if (s[-1] == '-')	//will add after
		else				//will add before
	}
}

/* Gives the number with minimum X amount of DIGITS. adding zeros before the number it self */
int	digit_amount(va_list *l, char *s, int *i)
{
	int	nbr;

	*i++;
	nbr = va_arg(*l, int);
	if (!f_isdigit(s[0]))
}

/** @brief
 * Used with x or X flags, it adds 0x or 0X before the conversion respectively, only if value isn't 0.
 * @param l
 * The list
 * @param s
 * String on the current index
 * @param i
 * Pointer to current index of string
 * @return
 * How many chars where printed, or -1 in case of error. */
int	base_teller(va_list *l, char *s, int *i)
{
	int	check;

	*i++;
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
		check = f_putnbr_u(va_arg(*l, unsigned int), "0123456789ABCDEF", 16) + 2;
		if (check == -1)
			return (-1);
		return (check + 2);
	}
	else
		return(print_arg(l, s, i));
}

/* puts space before a number if isn't negative. Only works with d or i flags */
int	print_space(va_list *l, char *s, int *i)
{
	int	nbr;
	int	check;

	*i++;
	if (s[0] != 'd' && s[0] != 'i')
		return(print_arg(l, s, i));
	nbr = va_arg(*l, int);
	if (nbr >= 0)
		write(1, " ", 1);
	check = ft_putnbr(nbr);
	if (check == -1)
		return (-1);
	return (check + 1);
}

/* puts a '+' before a number if isn't negative. Only works with d or i flags */
int	print_signal(va_list *l, char *s, int *i)
{
	int	nbr;
	int	check;

	*i++;
	if (s[0] != 'd' && s[0] != 'i')
		return(print_arg(l, s, i));
	nbr = va_arg(*l, int);
	if (nbr >= 0)
		write(1, "+", 1);
	check = ft_putnbr(nbr);
	if (check == -1)
		return (-1);
	return (check + 1);
}
