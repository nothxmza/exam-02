#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int ft_putchar(char c)
{
	write(1,&c,1);
	return(1);
}

int ft_count(long num, int base)
{
	int ret = 1;
	while(num>= base && ++ret)
		num = num /  base;
	return(ret);
}
int ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return(i);
}

void ft_putnum(long num ,int base_num)
{
	char *base = "0123456789abcdef";
	if(num >= base_num)
		ft_putnum((num / base_num), base_num);
	write(1, &base[num % base_num],1);
}

int ft_printf(const char *str, ...)
{
	va_list args;
	int i = 0;
	int j = 0;
	int width = 0;
	int char_count = 0;
	long num = 0;
	va_start(args, str);
	while(str[i])
	{
		if(str[i] == '%')
		{
			i+= 1;
			while(str[i] >= '0' && str[i] <= '9')
				width = width *10 + str[i++] - 48;
			if(str[i] == 's')
			{
				char *arg = va_arg(args,char *);
				if(!arg)
					arg = "(null)";
				else
					arg = arg;
				if(width > 0)
				{
					width -= ft_strlen(arg);
					while(width-- > 0)
						char_count += ft_putchar(' ');
				}
				while(arg[j])
					char_count += ft_putchar(arg[j++]);
			}
			else if (str[i] == 'd')
			{
				num = va_arg(args, int);
				if (width > 0)
				{
					if(num < 0)
					{
						num = num * -1;
						width -= ft_count(num,10) + 1;
						
					while(width-- > 0)
						char_count += ft_putchar(' ');
					char_count += ft_putchar('-');
					}
					else
					{
						width -= ft_count(num,10);
						while(width-- > 0)
							char_count += ft_putchar(' ');
					}
				}
				if(num < 0)
				{
					num = num * -1;
					char_count += ft_putchar('-');
				}
				char_count += ft_count(num, 10);
				ft_putnum(num,10);
			}
			else if (str[i] == 'x')
			{
				num = va_arg(args, unsigned int);
				char_count += ft_count(num,16);
				if(width > 0)
				{
					width -= ft_count(num,16);
					while(width-- > 0)
						char_count += ft_putchar(' ');
				}
				ft_putnum(num,16);
			}
		}
		else
			char_count += ft_putchar(str[i]);
		width = 0;
		i++;
	}
		va_end(args);
		return(char_count);
}
int main(void)
{
	int count = ft_printf("nehuwgehwbcewhv%5s,%d,%d,%3x,5%5d,5%5d\n","lala",INT_MAX,INT_MIN,10,-5,10);
	int countt = printf("nehuwgehwbcewhv%5s,%d,%d,%3x,5%5d,5%5d\n","lala",INT_MAX,INT_MIN,10,-5,10);
	printf("%d\n",count);
	printf("%d",countt);
//printf("nehuwgehwbcewhv%5s,%d,%d,%3x,5%d,5%d\n","lala",INT_MAX,INT_MIN,10,-5,10);
}