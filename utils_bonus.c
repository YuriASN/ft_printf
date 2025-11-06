#include "ft_printf_bonus.h"

int	justfy_left(va_list *l, char *s, int *i)
{

}

int	right_width(va_list *l, char *s, int *i)
{

}

int	digit_amount(va_list *l, char *s, int *i)
{
	int	nbr;

	if (s[0] != 'd' && s[0] != 'i')
		return(print_arg(l, s, i));
	nbr = va_arg(*l, int);
}

int	base_teller(va_list *l, char *s, int *i)
{
	if (s[0] != 'x' && s[0] != 'X')
		return(print_arg(l, s, i));
}

int	print_space(va_list *l, char *s, int *i)
{
	int	nbr;

	if (s[0] != 'd' && s[0] != 'i')
		return(print_arg(l, s, i));
	nbr = va_arg(*l, int);
}

int	print_signal(va_list *l, char *s, int *i)
{
	int	nbr;

	if (s[0] != 'd' && s[0] != 'i')
		return(print_arg(l, s, i));
	nbr = va_arg(*l, int);
}
