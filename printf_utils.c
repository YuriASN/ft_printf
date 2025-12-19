#include "ft_printf.h"

/* Convert the number (n) to the base (str) acoording to size of base (base) */
static int	base_conversor(ssize_t n, char *str, ssize_t base)
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
