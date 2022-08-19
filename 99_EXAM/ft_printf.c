#include <stdarg.h>
#include <unistd.h>

size_t ft_put_string(char *string, int length)
{
    while (string && string[length] && ++length);
    return string ? write(1, string, length) : write(1, "(null)", 6);
}

void ft_put_number(unsigned digits, unsigned length, char *sign, int *g_val)
{
    if (digits >= length)
        ft_put_number(digits / length, length, sign, g_val);
    *g_val += (int)write(1, &sign[digits % length], 1);
}

void ft_digits(long digits, int length, char *sign, int *g_val)
{
    (digits < 0) ? \
    (*g_val += (int)write(1, "-", 1), ft_put_number(-digits, length, sign, g_val)) \
    : ft_put_number(digits, length, sign, g_val);
}

int ft_printf(const char *format, ... )
{
    int g_val = 0;
    va_list ap;

    va_start(ap, format);
    while (*format)
    {
        if (*format == '%' && *(format+1) == 's' && (format += 2))
            g_val += (int)ft_put_string(va_arg(ap, char *), 0);
        else if (*format == '%' && *(format+1) == 'x' && (format += 2))
            ft_put_number(va_arg(ap, int), 16, "0123456789abcdef", &g_val);
        else if (*format == '%' && *(format+1) == 'd' && (format += 2))
            ft_digits(va_arg(ap, int), 10, "0123456789", &g_val);
        else
            g_val += (int)write(1, format++, 1);
    }
    return (va_end(ap), g_val); 
}
