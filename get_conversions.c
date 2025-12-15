#include "ft_printf_bonus.h"

/** @brief Get how many times a number can be divided by other. */
static int	hex_size(unsigned long nbr)
{
	int	count;

	count = 1;
	while (nbr / 16)
	{
		count++;
		nbr /= 16;
	}
	return (count);
}

/** @brief Get's the converted number to it's base 0, x or X. */
void	get_u_long(unsigned long n, char base, char *conv, int teller)
{
	char			*b;
	unsigned long	size;
//fprintf(stderr, "n = %ld\n", n);
	size = 10;
	if (base == 'x' || base == 'X')
		size = 16;
	if (base == 'x')
		b = "0123456789abcdef";
	else if (base == 'X')
		b = "0123456789ABCDEF";
	else
		b = "0123456789";
	if (n >= size)
		get_u_long(n / size, base, conv, teller);
	conv[hex_size(n) + teller - 1] = b[n % size];
}

/** @brief Get's the converted number to it's base 0, x or X. */
void	get_nbr(int n, char *conv, int sign)
{
	char	*b;
	int		size;

	size = 10;
	b = "0123456789";
	if (n < 0)
	{
		conv[0] = '-';
		sign--;
		n *= -1;
		get_nbr(n, conv, sign);
	}
	if (n > size)
		get_nbr(n / size, conv, sign);
	conv[get_digits(n) - sign] = b[n % size];
}
