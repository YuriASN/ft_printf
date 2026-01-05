#include "ft_printf_bonus.h"

/* Convert the number (n) to the base (str) acoording to size of base (base) */
static int	base_conversor(ssize_t n, char *str, ssize_t base)
{
	int	count;
	int	check;

	count = 0;
	if (n >= base)
		count = base_conversor(n / base, str, base);
	if (count == -1)
		return (-1);
	check = write(1, &str[n % base], 1);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}

/* Convert the unsigned long (n) to the base (str) acoording to size of base (base) */
static int	ul_base_conversor(unsigned long n, char *str, unsigned long base)
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
 * Returns the amount of digits that a number has,
 * without including the '-' in case of a negative number.
 * @param n The Number to count the digits.
 * @return The amount of digits of the number. */
int	get_digits(ssize_t n)
{
	int	digits;

	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	digits = 1;
	while (n / 10)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

int	f_putnbr_u(unsigned int n, char *str, ssize_t base)
{
	int				count;
	unsigned long	n2;

	n2 = n;
	count = ul_base_conversor(n2, str, base);
	return (count);
}

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
