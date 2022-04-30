#include <stdio.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void change_to_hex(char c)
{
    char *base;
    base = "0123456789abcdef";
    ft_putchar(base[c / 16]);
    ft_putchar(base[c % 16]);
}

int main()
{
    change_to_hex(10);
}