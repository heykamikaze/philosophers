#include "philo.h"

void	ft_exit(int index)
{
	if (index == 1)
		printf("%s", "MEMORY ERROR");
	if (index == 2)
		printf("%s", "ARG ERROR");
	exit (EXIT_FAILURE);
}

int	ft_is_digit(int c)
{
	if (c <= 47 || c >= 58)
		ft_exit(2);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			a;
	long int	b;
	long int	negative;

	a = 0;
	b = 0;
	negative = 1;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == 32)
		a++;
	if (str[a] == 45 || str[a] == 43)
	{
		if (str[a] == 45)
			negative *= -1;
		a++;
	}
	while (str[a] >= 48 && str[a] <= 57)
	{
		b = b * 10 + (str[a] - 48);
		if (b * negative > 2147483647)
			return (-1);
		else if (b * negative < -2147483648)
			return (0);
		a++;
	}
	return (b * negative);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

void	ft_putnbr(long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr((n / 10));
		ft_putchar('0' + n % 10);
	}
	else
		ft_putchar('0' + n);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}