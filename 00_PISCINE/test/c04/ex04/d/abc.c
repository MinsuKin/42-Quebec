#include <unistd.h>

int		abs(int n)
{
	return (n < 0 ? -n : n);
}

int		fstrlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		check_base(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	i = 0;
	while (i < base[i + 1])
	{
		j = i + 1;
		while (j < base[j])
		{
			if (base[i] >= base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	helper(int nbr, char *base, int b)
{
	if (nbr < 0)
	{
		write(1, "-", 1);
		if (abs(nbr / b))
			helper(abs(nbr / b), base, b);
		helper(abs(nbr % b), base, b);
	}
	else if (nbr < b)
		write(1, &base[nbr], 1);
	else
	{
		helper(nbr / b, base, b);
		helper(nbr % b, base, b);
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	int b;

	b = fstrlen(base);
	if (!base || b < 2 || !check_base(base))
		return ;
	helper(nbr, base, b);
}

#include <stdio.h>

void	ft_putnbr_base(int nbr, char *base);

int 	main()
{
	ft_putnbr_base(-2147483648, "0123456789"); printf("\n");
	ft_putnbr_base(-2147483648, "01");printf("\n");
	ft_putnbr_base(-2147483648, "0123456789ABCDEF");printf("\n");
	ft_putnbr_base(-2147483648, "01234567");printf("\n");
	ft_putnbr_base(2147483647, "0123456789"); printf("\n");
	ft_putnbr_base(2147483647, "01");printf("\n");
	ft_putnbr_base(2147483647, "0123456789ABCDEF");printf("\n");
	ft_putnbr_base(2147483647, "01234567");
	ft_putnbr_base(2147483647, "0");printf("\n");
	ft_putnbr_base(2147483647, "-0123456789ABCDEF");printf("\n");
	ft_putnbr_base(2147483647, "  0123456789ABCDEF");printf("\n");
}