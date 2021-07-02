#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
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

int main(int argc,char **argv)
{
	if (argc != 3)
	{
		ft_putchar('\n');
		return(0);
	}
	else{
		int i = 0;
		int x =0;
		int j = 0;
		char *str1;
		char *str2;
		char str3[255];

		str1 = argv[1];
		str2 = argv[2];
		while(str1[i])
		{
			while(str2[x])
			{
				if(str1[i] == str2[x])
				{
					if(!ft_exist(str3,str1[i]))
						str3[j++] = str1[i];
				}
				x++;
			}
			x = 0;
			i++;
		}
		str3[j] = '\0';
		j = 0;
		while(str3[j])
			ft_putchar(str3[j++]);
		ft_putchar('\n');
	}
	return(0);
}	