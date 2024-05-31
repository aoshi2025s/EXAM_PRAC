// https://github.com/pasqualerossi/42-School-Exam-Rank-03/blob/main/ft_printf/ft_printf.c

#include <unistd.h>
#include <stdarg.h>

void    put_string(char *str, int *len)
{
    if (!str)
        str = "(null)";
    while (*str)
        *len += write(1, str++, 1);
}

void    put_digit(long long int num, int base, int *len)
{
    char *hex = "0123456789abcdef";

    if (num < 0)
    {
        num *= -1;
        *len += write(1, "-", 1);
    }
    if (num >= base)
        put_digit((num / base), base, len);
    *len += write(1, &hex[num % base], 1);
}

int ft_printf(const char *fmt, ...)
{
    int len = 0;

    va_list ptr;
    va_start(ptr, fmt);

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            if (*fmt == 's')
                put_string(va_arg(ptr, char *), &len);
            else if (*fmt == 'd')
                put_digit((long long int)va_arg(ptr, int), 10, &len);
            else if (*fmt == 'x')
                put_digit((long long int)va_arg(ptr, unsigned int), 16, &len);
            else
                return (va_end(ptr), -1);
        }
        else
            len += write(1, fmt, 1);
        fmt++;
    }
    return (va_end(ptr), len);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     char *str = "Hello, World!";
//     char *str_null = NULL;

//     int result;
//     int expected;

//     result = ft_printf("%s\n",str);
//     expected = printf("%s\n", str);
//     if (result == expected)
//         printf("%%s test passed\n");
//     else
//         printf("%%s test failed\n");
    
//     result = ft_printf("%s\n",str_null);
//     expected = printf("%s\n", str_null);
//     if (result == expected)
//         printf("%%s test passed\n");
//     else
//         printf("%%s test failed\n");


//     int d = -214345868;
//     result = ft_printf("%d\n", d);
//     expected = printf("%d\n", d);
//     if (result == expected)
//         printf("%%s test passed\n");
//     else
//         printf("%%s test failed\n");

//     int hex = 42;
//     result = ft_printf("%x\n", hex);
//     expected = printf("%x\n", hex);
//     if (result == expected)
//         printf("%%s test passed\n");
//     else
//         printf("%%s test failed\n");
// }
