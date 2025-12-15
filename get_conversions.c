#include "ft_printf_bonus.h"

/** @brief Get's the converted number to it's base 0, x or X. */
void	get_u_long(unsigned long n, char base, char *conv, int sign)
{
	char			*b;
	unsigned long	size;

	size = 10;
	if (base == 'x' || base == 'X')
		size = 16;
	if (base == 'x')
		b = "0123456789abcdef";
	else if (base == 'X')
		b = "0123456789ABCDEF";
	else
		b = "0123456798";
	if (n > size)
		get_u_long(n / size, base, conv, sign);
	conv[get_digits(n) - sign] = b[n % size];
}

/** @brief Get's the converted number to it's base 0, x or X. */
void	get_nbr(int n, char base, char *conv, int sign)
{
	char	*b;
	int		size;

	size = 10;
	if (base == 'x' || base == 'X')
		size = 16;
	if (n < 0)
	{
		conv[0] = '-';
		sign--;
		n *= -1;
		get_nbr(n, base, conv, sign);
	}
	if (base == 'x')
		b = "0123456789abcdef";
	else if (base == 'X')
		b = "0123456789ABCDEF";
	else
		b = "0123456798";
	if (n > size)
		get_nbr(n / size, base, conv, sign);
	conv[get_digits(n) - sign] = b[n % size];
}
