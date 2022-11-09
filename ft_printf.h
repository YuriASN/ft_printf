/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysantos- <ysantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:39:14 by ysantos-          #+#    #+#             */
/*   Updated: 2022/06/05 21:52:17 by ysantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# define LLONG unsigned long long

int	ft_printf(const char *str, ...);
int	f_putnbr(int n);
int	base_conversor(LLONG n, char *str, LLONG base);
int	f_putnbr_u(unsigned int n, char *str, LLONG base);
int	f_putnbr_ul(unsigned long n);

#endif
