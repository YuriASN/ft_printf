#include "ft_printf_bonus.h"

/** @brief Get the amount of digits the number will have in a base.
 * @param nbr
 * Number to check for amount digits in hex base. */
static int	hex_size_long(unsigned long nbr)
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

/** @brief Get the amount of digits the number will have in a base.
 * @param nbr
 * Number to check for amount of digits in given base.
 * @param base
 * Size of the base he will be transformed. */
static int	convert_size_unsig(unsigned int nbr, char base)
{
	int	count;

	count = 1;
	if (base == '0')
	{
		while (nbr / 10)
		{
			count++;
			nbr /= 10;
		}
	}
	else
	{
		while (nbr / 16)
		{
			count++;
			nbr /= 16;
		}
	}
	return (count);
}

/** @brief Converte number to base 0, x or X.
 * @param n
 * Unsigned int to be converted to char*
 * @param base
 * Letter giving the base to be converted to.
 * @param conv
 * String that conversion will be set on.*/
void	get_unsig(unsigned int n, char base, char *conv)
{
	char			*b;
	unsigned int	size;
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
		get_unsig(n / size, base, conv);
	conv[convert_size_unsig(n, base) - 1] = b[n % size];
}

/** @brief Converte number to hex base.
 * @param n
 * Unsigned long to be converted to char*
 * @param conv
 * String that conversion will be set on. */
void	get_unsig_long(unsigned long n, char *conv)
{
	char			*b;
	unsigned long	size;
//fprintf(stderr, "n = %ld\n", n);
	size = 16;
	b = "0123456789abcdef";
	if (n >= size)
		get_unsig_long(n / size, conv);
	conv[hex_size_long(n) - 1] = b[n % size];
}

/** @brief Transforms the int to char*. No allocation is done.
 * @param n
 * Number to be converted in char*.
 * @param conv
 * String to store the conversion.
 * @param sign
 * Flag to save space for '-' sign. */
void	get_nbr(ssize_t n, char *conv, int sign)
{
	char	*b;
	int		size;

	size = 10;
	b = "0123456789";
	if (n < 0)
	{
		conv[0] = '-';
		sign = 0;
		n *= -1;
		get_nbr(n, conv, sign);
	}
	if (n >= size)
		get_nbr(n / size, conv, sign);
	conv[get_digits(n) - sign] = b[n % size];
}
