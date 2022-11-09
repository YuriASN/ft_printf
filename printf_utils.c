/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysantos- <ysantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:59:44 by ysantos-          #+#    #+#             */
/*   Updated: 2022/09/29 21:13:22 by ysantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	f_putnbr(int n)
{
	int			count;
	long long	n2;

	count = 0;
	n2 = n;
	if (n2 < 0)
	{
		count += write(1, "-", 1);
		n2 *= -1;
	}
	count += base_conversor(n2, "0123456789", 10);
	return (count);
}

int	f_putnbr_u(unsigned int n, char *str, LLONG base)
{
	int			count;
	long long	n2;

	count = 0;
	n2 = n;
	count += base_conversor(n2, str, base);
	return (count);
}

int	f_putnbr_ul(unsigned long n)
{	
	int			count;
	long long	n2;

	if (n == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count = write(1, "0x", 2);
	n2 = n;
	count += base_conversor(n2, "0123456789abcdef", 16);
	return (count);
}

/* Convert the number (n) to the base (str) acoording to size of base (base) */
int	base_conversor(LLONG n, char *str, LLONG base)
{
	int	c;

	c = 0;
	if (n >= base)
		c = base_conversor(n / base, str, base);
	c += write(1, &str[n % base], 1);
	return (c);
}
