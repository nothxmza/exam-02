#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int ft_putchar(char c)
{
	write(0, &c, 1);
	return(1);
}
int    ft_len(long int nbr)
{
    int        len;

    len = (nbr <= 0) ? 1 : 0;
    while (nbr != 0)
    {
        nbr = nbr / 10;
        len++;
    }
    return (len);
}


int	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int		convert_base1(unsigned long long nbr, int base)
{
	int		i;

	i = 0;
	while (nbr != 0)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	unsigned int	nb;
	int char_count;

	char_count = ft_len(n);

	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	nb = (unsigned int)n;
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + 48);
	return(char_count);
}
char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	if ((dest = malloc(ft_strlen(s) * sizeof(char) + 1)) == 0)
		return (0);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char	*convert_base(unsigned long long nbr, int base)
{
	int					i;
	unsigned long long	n;
	char				*str;

	i = 0;
	n = nbr;
	if (nbr == 0)
		return (ft_strdup("0"));
	i = convert_base1(nbr, base);
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (0);
	str[i] = '\0';
	while (n != 0)
	{
		if ((n % base) < 10)
			str[i - 1] = (n % base) + 48;
		else
			str[i - 1] = (n % base) + 55;
		n /= base;
		i--;
	}
	return (str);
}
int		ft_atoi(const char *str)
{
	unsigned int	num;
	int				i;
	int				np;

	np = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' ||
			str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			np = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(np * num));
}
int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int		ft_treat_hexa(unsigned int nbr)
{
	int		char_count;
	int		i;
	char	*hexa;

	char_count = 0;
	i = 0;
	nbr = (unsigned int)(4294967295 + 1 + nbr);
	hexa = convert_base((unsigned long long)nbr, 16);
	while (hexa[i])
	{
		char_count += ft_putchar(tolower(hexa[i++]));
		
	}
	/*if (width < 0)
		width *= -1;
	if (width > 0)
		char_count += ft_add_space(width - char_count);*/
	free(hexa);
	return (char_count);
}

int		ft_count_hexa(unsigned int nbr)
{
	int		char_count;
	int		i;
	char	*hexa;

	char_count = 0;
	i = 0;
	nbr = (unsigned int)(4294967295 + 1 + nbr);
	hexa = convert_base((unsigned long long)nbr, 16);
	while (hexa[i])
			i++;
	free(hexa);
	return (i);
}


int		ft_treatment(const char *str, va_list args)
{
	int		char_count;
	int i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '.' && ft_isdigit(str[i + 2]))
			{
				int count;
				char tab[100];
				int nbr;
				int x = 0;
				i += 2;
				while(ft_isdigit(str[i]))
					tab[x++] = str[i++];
				x = 0;
				nbr = ft_atoi(tab);
				if (str[i] == 's')
				{
					char *arg = va_arg(args,char*);
					count = ft_strlen(arg) - nbr;
					int j = 0;
					if (ft_strlen(arg) <= nbr)
					{
						while(arg[j])
							char_count += ft_putchar(arg[j++]);
					}
					while(j < count)
						char_count += ft_putchar(arg[j++]);
				}
				else if (str[i] == 'd')
				{
					int j = 0;
					int arg = va_arg(args,int);
					if (nbr > ft_len(arg))
					{
						while(nbr > ft_len(arg))
						{
							char_count += ft_putchar('0');
							nbr--;
						}
						char_count += ft_putnbr(arg);	
					}
					else if (nbr <= ft_len(arg))
						char_count += ft_putnbr(arg);
				}
				else if (str[i] == 'x')
				{
					int j = 0;
					int arg = va_arg(args,int);
					
					if (nbr > ft_count_hexa(arg))
					{
						while(nbr > ft_count_hexa(arg))
						{
							char_count += ft_putchar('0');
							nbr--;
						}
						char_count += ft_treat_hexa(arg);	
					}
					else if (nbr <= ft_count_hexa(arg))
						char_count += ft_treat_hexa(arg);

				}
			}
			else if (str[i + 1]  == 's')
			{
				int j = 0;
				i += 1;
				char *arg = va_arg(args,char*);
				while(arg[j])
					char_count += ft_putchar(arg[j++]);
			}
			else if (str[i + 1] == 'd')
			{
				i += 1;
				int arg = va_arg(args, int);
				char_count += ft_putnbr(arg);	
			}
			else if (str[i+1] == 'x')
			{
				i += 1;
				char_count += ft_treat_hexa(va_arg(args, unsigned int));
			}
		}
		else
			char_count += ft_putchar(str[i]);
			
		i++;
	}
	return (char_count);
}

int		ft_printf(const char *str, ...)
{
	int		char_count;
	va_list	args;

	char_count = 0;
	va_start(args, str);
	char_count += ft_treatment(str, args);
	va_end(args);
	return (char_count);
}

int main(void)
{
int i  = 123;
	ft_printf("faux %.1d\n",i);
	printf("vrai %.3d\n",i);
}