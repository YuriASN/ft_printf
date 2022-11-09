/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysantos- <ysantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:16:04 by ysantos-          #+#    #+#             */
/*   Updated: 2022/06/05 21:50:01 by ysantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	f_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	f_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		++i;
	return (i);
}

static int	f_putstr(char *str)
{
	if (!str)
		str = "(null)";
	return (write(1, str, f_strlen(str)));
}

static int	print_arg(va_list *l, char c)
{
	if (c == 'c')
		return (f_putchar(va_arg(*l, int)));
	if (c == 's')
		return (f_putstr(va_arg(*l, char *)));
	if (c == 'd' || c == 'i')
		return (f_putnbr(va_arg(*l, int)));
	if (c == 'u')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789", 10));
	if (c == 'x')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789abcdef", 16));
	if (c == 'X')
		return (f_putnbr_u(va_arg(*l, unsigned int), "0123456789ABCDEF", 16));
	if (c == 'p')
		return (f_putnbr_ul(va_arg(*l, unsigned long)));
	if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	l;

	i = -1;
	count = 0;
	va_start(l, str);
	while (str[++i])
	{
		if (str[i] == '%')
			count += print_arg(&l, str[++i]);
		else
			count += write(1, &str[i], 1);
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
