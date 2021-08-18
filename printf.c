#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_count(long num, int base_num)
{
	int	 ret = 1;
	while (num >= base_num && ++ret)
		num = num / base_num;
	return (ret);
}

void	ft_putnum(long num, int base_num)
{
	char *base = "0123456789abcdef";
	if (num >= base_num)
		ft_putnum((num / base_num), base_num);
	write(1, &base[num % base_num], 1);
}

int	ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list args;
	long num = 0;
	int	i = 0, char_count = 0, j = 0, width = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i += 1;
			while (str[i] >=  '0' && str[i] <= '9')
				width = width * 10 + str[i++] - 48;
			if (str[i] == 's')
			{
				char *argument = va_arg(args, char *);
			 	if(!argument)
					argument = "(null)";
				else
					argument = argument;
				if (width > 0)
				{
					width -= ft_strlen(argument);
					while (width-- > 0)
						char_count += ft_putchar(' ');
					while (argument[j])
						char_count+= ft_putchar(argument[j++]);
				}
				else
				{
					while (argument[j])
						char_count+= ft_putchar(argument[j++]);
				}
			}
			else if (str[i] == 'd')
			{
				num = va_arg(args, int);
				if (width > 0)
				{
					if (num < 0)
					{
						num = num * -1;
						width -= ft_count(num, 10);
						width -= 1;
						while (width-- > 0)
							char_count += ft_putchar(' ');
						char_count += ft_putchar('-');
					}
					else
						width -= ft_count(num, 10);
						while (width-- > 0)
							char_count += ft_putchar(' ');
				}
				if (num < 0)
				{
					num = num * -1;
					char_count += ft_putchar('-');
				}
				char_count += ft_count(num, 10);
				ft_putnum(num, 10);
			}
			else if (str[i] == 'x')
			{
				num = va_arg(args, unsigned int);
				char_count+= ft_count(num, 16);
				if (width > 0)
				{
					width -= ft_count(num, 16);
					while (width-- > 0)
						char_count += ft_putchar(' ');
				}
				ft_putnum(num, 16);
			}
		}
		else
			char_count += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (char_count);
}

int main(void)
{
	int count = ft_printf("%5d, %d\n",INT_MAX, INT_MIN);
	int countt = printf("%5d, %d\n",INT_MAX, INT_MIN);
	printf("%d",count);
	printf("%d",countt);
}
