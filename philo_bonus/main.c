/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:55:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/18 14:55:36 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include <unistd.h>

void put_string(char *str, int *length)
{
	if (!str)
		str = "(null)";
	while (*str)
		*length += write(1, str++, 1);
}

void put_number(long long int number, int base, int *length)
{
	char *hexa = "0123456789abcdef";
	
	if (number < 0)
	{
		number *= -1;
		*length += write(1, "-", 1);
	}
	if (number >= base)
		put_number(number / base, base, length);
	*length += write(1, &hexa[number % base], 1);
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	int length = 0;

	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && (*(format + 1) == 's' || *(format + 1) == 's' || *(format + 1) == 's'))
		{
			format++;
			if (*format == 's')
				put_string(va_arg(ap, char *), &length);
			if (*format == 'd')
				put_number((long long int)va_arg(ap, int), 10, &length);
			if (*format == 'x')
				put_number((long long int)va_arg(ap, unsigned int), 16, &length);
		}
		else
			length += write(1, format, 1);
		format++;
	}
	return (va_end(ap), length);
}