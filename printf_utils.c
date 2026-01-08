#include "ft_printf.h"

/** @brief
 * Print to stdout the given number on the given base.
 * @param n
 * Number to be converted.
 * @param str
 * String with the base to convert
 * @param base
 * Size of the base of str.
 * @return
 * Amount of characters that were put on stdout. */
static int	base_conversor(long long n, char *str, ssize_t base)
{
	int	c;
	int	check;

	c = 0;
	if (n >= base)
		c = base_conversor(n / base, str, base);
	if (c == -1)
		return (-1);
	check = write(1, &str[n % base], 1);
	if (check == -1)
		return (-1);
	c += check;
	return (c);
}

/** @brief
 * Print to stdout the given unsigned long on the given base.
 * @param n
 * Unsigned long to be converted.
 * @param str
 * String with the base to convert
 * @param base
 * Size of the base of str.
 * @return
 * Amount of characters that were put on stdout. */
static int	ul_base_conversor(unsigned long n, char *str, unsigned long base)
{
	int	c;
	int	check;

	c = 0;
	if (n >= base)
		c = ul_base_conversor(n / base, str, base);
	if (c == -1)
		return (-1);
	check = write(1, &str[n % base], 1);
	if (check == -1)
		return (-1);
	c += check;
	return (c);
}

/** @brief
 * Puts on stdout the int passed as a parameter.
 * @param n Int to be displayed. */
int	f_putnbr(int n)
{
	int			count;
	int			check;
	long long	n2;

	count = 0;
	n2 = n;
	if (n2 < 0)
	{
		count = write(1, "-", 1);
		if (count == -1)
			return (-1);
		n2 *= -1;
	}
	check = base_conversor(n2, "0123456789", 10);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}

/** @brief
 * Puts on stdout the unsigned int passed as a parameter on the given base.
 * @param n Unsigned int to be displayed.
 * @param str Base to be converted to.
 * @param base Size of (str) base. */
int	f_putnbr_u(unsigned int n, char *str, ssize_t base)
{
	int			count;
	long long	n2;

	n2 = n;
	count = base_conversor(n2, str, base);
	return (count);
}

/** @brief
 * Puts on stdout the unsigned long passed as a parameter on the given base.
 * Only used for 'p' flag (memory address).
 * @param n Unsigned long to be displayed. */
int	f_putnbr_ul(unsigned long n)
{
	int			count;
	int			check;

	if (n == 0)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	if (count == -1)
		return (-1);
	check = ul_base_conversor(n, "0123456789abcdef", 16);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}
