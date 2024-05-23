/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoaoki <yoaoki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:41:00 by yoaoki            #+#    #+#             */
/*   Updated: 2024/05/24 01:17:06 by yoaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // for write function
#include <stdlib.h> // for malloc, free function
#include <stdarg.h> // for va_arg function

# define BASE "0123456789abcdef"

int ft_strlen(char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return (len);
}

int ft_putchar_fd(int fd, char c)
{
	return (write(fd, &c, 1));
}

int ft_putstr_fd(int fd, char *str)
{
	int len = ft_strlen(str);
	return (write(fd, str, len));
}

void ft_putnbr_fd(int fd, long long num)
{
	if (num < 0)
	{
		num = -num;
		ft_putchar_fd(fd, '-');
	}
	if (num >= 10)
	{
		ft_putnbr_fd(fd, num / 10);
		ft_putchar_fd(fd, num % 10 + '0');
	}
	if (num < 10)
	{
		ft_putchar_fd(fd, num % 10 + '0');
	}
}

void ft_puthex_fd(int fd, unsigned long long num)
{
	if (num >= 16)
	{
		ft_puthex_fd(fd, num / 16);
		ft_putchar_fd(fd, BASE[num % 16]);
	}
	if (num < 16)
	{
		ft_putchar_fd(fd, BASE[num % 16]);
	}
}

int ft_print_char(va_list *ap)
{
	char c = va_arg(*ap, int);
   return (ft_putchar_fd(1, c));
}

int ft_print_str(va_list *ap)
{
	char *str = va_arg(*ap, char *);
	if (!str)
		return (ft_putstr_fd(1, "(null)"));
	return (ft_putstr_fd(1, str));
}

int ft_numlen(int n)
{
	long long num = n;
	int len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len = 1;
		num = -num;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

int ft_print_nbr(va_list *ap)
{
	int n = va_arg(*ap, int);
	ft_putnbr_fd(1, n);
	return (ft_numlen(n));
}

int ft_hexlen(unsigned long long num)
{
	int len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		len++;
		num /= 16;
	}
	return (len);
}

int ft_print_hex(va_list *ap)
{
	unsigned long long hex = va_arg(*ap, unsigned long long);
	ft_puthex_fd(1, hex);
	return (ft_hexlen(hex));
}


int ft_put_convert(va_list *ap, char c)
{
	if (c == 's')
		return (ft_print_str(ap));
	if (c == 'd')
		return (ft_print_nbr(ap));
	if (c == 'x')
		return (ft_print_hex(ap));
	return (-1);	
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	int	result;
	
	result = 0;	
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			result += ft_put_convert(&ap, *format++);
		}
		else
		{
			result += ft_putchar_fd(1, *format);
			format++;
		}
	}
	va_end(ap);
	return (result);

}
/*
#include <stdio.h>

int main(void)
{
	//char *str = "Hello, World";
	char *str = NULL;	
	int num = -2147483648;
	//int num = -1233;
	//int hex = 2137483648;
	//int hex = 42;
	//int hex = 5454;
	int hex = -2147483648;
	int result;
	int expected;
	
	result = ft_printf("string: %s\n", str);
	expected = printf("string: %s\n", str);
	if(result == expected)
		printf("%%s test is ok\n");
	else
		printf("%%s test failed\n, result = %d, expected = %d\n", result, expected);

	
	result = ft_printf("num: %d\n", num);
	expected = printf("num: %d\n", num);
	if(result == expected)
		printf("%%nbr test is ok\n");
	else
		printf("%%nbr test failed\n");

	
	result = ft_printf("hex: %x\n", hex);
	expected = printf("hex: %x\n", hex);
	if(result == expected)
		printf("%%hex test is ok\n");
	else
		printf("%%hex test failed\n");

	result = ft_printf("this is special test \
			num: %d, hex: %x, str: %s\n", num, hex, str);
	expected = printf("this is special test \
			num: %d, hex: %x, str: %s\n", num, hex, str);
	if (result == expected)
		printf("special test is ok\n");
	else
		printf("special test failed\n");

}
*/
