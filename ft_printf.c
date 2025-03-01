/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:19:22 by habdella          #+#    #+#             */
/*   Updated: 2025/01/10 13:19:43 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "stdarg.h"

int	putlchar(char c)
{
	write(2, &c, 1);
	return (1);
}

int	putlstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i += putlstr("(null)"));
	while (s[i])
	{
		write (2, &s[i], 1);
		i++;
	}
	return (i);
}

int	putlnbr(int nb)
{
	long	nbl;
	int		len;

	nbl = nb;
	len = 0;
	if (nbl < 0)
	{
		nbl = -nbl;
		putlchar('-');
		len++;
	}
	if (nbl > 9)
		len += putlnbr(nbl / 10);
	putlchar(nbl % 10 + 48);
	len++;
	return (len);
}

int	check_format(va_list list, const char *format, int i)
{
	if (format[i] == 'c')
		return (putlchar(va_arg(list, int)));
	else if (format[i] == 's')
		return (putlstr(va_arg(list, char *)));
	else if (format[i] == 'd' || format[i] == 'i')
		return (putlnbr(va_arg(list, int)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!format)
		return (-1);
	va_start(list, format);
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX\%", format[i + 1]))
		{
			len += check_format(list, format, i + 1);
			i += 2;
		}
		else
		{
			len += putlchar(format[i]);
			i++;
		}
	}
	va_end(list);
	return (len);
}
