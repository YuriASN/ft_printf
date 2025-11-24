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
	int			count;
	long long	n2;

	n2 = n;
	count = base_conversor(n2, str, base);
	return (count);
}

int	f_putnbr_ul(unsigned long n)
{
	int			count;
	int			check;
	long long	n2;

	if (n == 0)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	if (count == -1)
		return (-1);
	n2 = n;
	check = base_conversor(n2, "0123456789abcdef", 16);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}
