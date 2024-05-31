// https://github.com/pasqualerossi/42-School-Exam-Rank-03/blob/main/ft_printf/ft_printf.c

#include <unistd.h>
#include <stdarg.h>

void    put_string(char *string, int *length)
{
    if (!string)
        string = "(null)";
    while (*string)
        *length += write(1, string++, 1);
}

void    put_digit(long long int number, int base, int *length)
{
    char *hexademical = "0123456789abcdef";

    if (number < 0)
    {
        number *= -1;
        *length += write(1, "-", 1);
    }
    if (number >= base)
        put_digit((number / base), base, length);
    *length += write(1, &hexademical[number % base], 1);
}

int ft_printf(const char *format, ...)
{
    int length = 0;

    va_list pointer;
    va_start(pointer, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 's')
                put_string(va_arg(pointer, char *), &length);
            else if (*format == 'd')
                put_digit((long long int)va_arg(pointer, int), 10, &length);
            else if (*format == 'x')
                put_digit((long long int)va_arg(pointer, unsigned int), 16, &length);
            else
                return (va_end(pointer), -1);
        }
        else
            length += write(1, format, 1);
        format++;
    }
    return (va_end(pointer), length);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str = "Hello, World!";
    char *str_null = NULL;

    int result;
    int expected;

    result = ft_printf("%s\n",str);
    expected = printf("%s\n", str);
    if (result == expected)
        printf("%%s test passed\n");
    else
        printf("%%s test failed\n");
    
    result = ft_printf("%s\n",str_null);
    expected = printf("%s\n", str_null);
    if (result == expected)
        printf("%%s test passed\n");
    else
        printf("%%s test failed\n");


    int d = -214345868;
    result = ft_printf("%d\n", d);
    expected = printf("%d\n", d);
    if (result == expected)
        printf("%%s test passed\n");
    else
        printf("%%s test failed\n");

    int hex = 42;
    result = ft_printf("%x\n", hex);
    expected = printf("%x\n", hex);
    if (result == expected)
        printf("%%s test passed\n");
    else
        printf("%%s test failed\n");
}
*/