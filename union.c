//union

#include <unistd.h>

void ft_putchar(char c)
{
	write(1,&c, 1);
}

int ft_exist(char *str, char c)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return(1);
		i++;
	}
	return(0);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putchar('\n');
		return(0);
	}
	else{
		char *str1;
		char *str2;
		char str3[255];
		int i = 0;
		int x = 0;

		str1 = argv[1];
		str2 = argv[2];
		while(str1[i])
		{
			if (!ft_exist(str3,str1[i]))
				str3[x++] = str1[i];
			i++;
		}
		i = 0;
		while(str2[i])
		{
			if(!ft_exist(str3,str2[i]))
				str3[x++] = str2[i];
			i++;
		}
		str3[x] = '\0';
		x = 0;
		while(str3[x])
			ft_putchar(str3[x++]);
		ft_putchar('\n');
	}
	return(0);
}