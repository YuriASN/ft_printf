#include "ft_printf_bonus.h"

static int	print_bonus_arg(va_list *l, const char *c, int *i)
{
	//increment i accordingly to the flags, -1 that's already done.
	if (c[0] == '-')	//in combination with a value sets the chars (next if) after the arg, instead of before
		return (justfy_left(l, &c[1], i));
	if (ft_isdigit(c[0]))	//Gives the argument with minimum X amount of CHARS. In case the first number is 0 and arg is d or i, it adds zero to complement, otherwise add spaces.
		return (justfy_right(l, c, i));
	if (c[0] == '.')	//Gives the number with minimum X amount of DIGITS. adding zeros before the number it self
		return (digit_amount(l, &c[1], i));
	if (c[0] == '#')	//Used with x or X flags, it adds 0x or 0X before the conversion respectively, only if value isn't 0.
		return (base_teller(l, &c[1], i));
	if (c[0] == ' ')	//puts space before a number if isn't negative. Only works with d or i flags
		return (print_space(l, &c[1], i));
	if (c[0] == '+')	//puts a '+' before a number if isn't negative. Only works with d or i flags
		return (print_signal(l, &c[1], i));
	return (write(1, "", 0));	//change to write the ""
}

int	print_arg(va_list *l, const char *c, int *i)
{
	char	letter;

	if (c[0] == 'c')
	{
		letter = (char)va_arg(*l, int);
		return (write(1, &letter, 1));
	}
	if (c[0] == 's')
		return (ft_putstr_fd(va_arg(*l, char *), 1));
	if (c[0] == 'd' || c[0] == 'i')
		return (ft_putnbr_fd(va_arg(*l, int), 1));
	if (c[0] == 'u')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789", 10));
	if (c[0] == 'x')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789abcdef", 16));
	if (c[0] == 'X')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789ABCDEF", 16));
	if (c[0] == 'p')
		return (f_putnbr_ul(va_arg(*l, unsigned long)));
	if (c[0] == '%')
		return (write(1, "%", 1));
	return (print_bonus_arg(l, c, i));
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	int		last;
	va_list	l;

	if (!str)
		return (-1);
	i = -1;
	count = 0;
	va_start(l, str);
	while (str[++i])
	{
		if (str[i] == '%')
			last = print_arg(&l, &str[++i], &i);
		else
			last = write(1, &str[i], 1);
		if (last == -1)
			return (-1);
		count += last;
	}
	va_end(l);
	return (count);
}

/* int	main(void)
{
	char	*str = "Hello world!";
	int		i = 145;
	int		x;

	x = printf("Essa porra vai dar %s | %i | addrs:%p\n", str, i, &i);
	i = ft_printf("Essa porra vai dar %s | %i | addrs:%p\n", str, i, &i);
	printf("i = %i  x = %i\n", i, x);
	return (0);
} */
