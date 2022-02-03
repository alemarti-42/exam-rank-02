#include<unistd.h>

int	chr_is_in(char chr, char *str)
{
	int i = 0;
	while (str[i])
		if (str[i++] == chr)
			return (1);
	return (0);
}


int	main(int argc, char *argv[])
{
	int i = 0;
	int j = 0;
	char	res[255];

	while(i < 255)
		res[i++] = 0;
	if (argc == 3)
	{
		i = 0;
		while (argv[1][i])
		{
			if(chr_is_in(argv[1][i], argv[2]) && !chr_is_in(argv[1][i], res))
			{
				res[j] = argv[1][i];	
				j++;
			}
			i++;
		}

	}
	i = 0;
	while (res[i])
	{
		write(1, &res[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
