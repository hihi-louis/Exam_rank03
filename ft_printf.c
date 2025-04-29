/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 05:01:41 by tripham           #+#    #+#             */
/*   Updated: 2025/04/29 05:19:04 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
int ft_putstr(const char *s)
{
	int total = 0;
	if (!s)
		return 0;
	int i = 0;
	while (s[i])
	{
		total += write(1, &s[i], 1);
		i++;
	}
	return total;
}

int ft_putnbr(long num, int base)
{
	char *base_type = "0123456789abcdef";
	int total = 0;
	if (num < 0)
	{
		total += write(1, "-", 1);
		num = -num;
	}
	if (num < base)
	{
		total += write(1, &base_type[num], 1);
	}
	if (num > base)
	{
		total += ft_putnbr(num / base, base);
		total += ft_putnbr(num % base, base);
	}
	return total;
}

int printf_help(va_list args, const char *s)
{
	int total = 0;
	int i = 0;
	while (s[i])
	{
		if (s[i] != '%')
			total += write(1, &s[i], 1);
		else
		{
			++i;
			if (s[i] == 's')
				total += ft_putstr(va_arg(args, const char *));
			if (s[i] == 'd')
				total += ft_putnbr(va_arg(args, int), 10);
			if (s[i] == 'x')
				total += ft_putnbr(va_arg(args, unsigned int), 16);
		}
		i++;
	}
	return (total);
}

int ft_printf(const char *s, ...)
{
	int total = 0;
	va_list args;
	va_start (args, s);
	total += printf_help(args, s);
	va_end(args);
	return 0;	
}

#include <stdio.h>

int main()
{
	int a = 42;
	char *s = "hello how are you";
	printf("%s\n", s);
	ft_printf("%s\n", s);
	printf("%d\n", a);
	ft_printf("%d\n",a);
	printf("%x\n", a);
	ft_printf("%x\n", a);
	return 0;
}