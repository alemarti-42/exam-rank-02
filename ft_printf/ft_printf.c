#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>


int	ft_printf(char *str, ...);

int	main()
{
	printf("TEST1:%d\n", ft_printf("Hola Mundo"));
	printf("TEST1:%d\n", printf("Hola Mundo"));
	printf("TEST2:%d\n", ft_printf("Hola %s", "Mundo"));
	printf("TEST2:%d\n", printf("Hola %s", "Mundo"));
	printf("TEST2:%d\n", ft_printf("Hola %s %s", NULL, "Mundo"));
	printf("TEST2:%d\n", printf("Hola %s %s", NULL, "Mundo"));
	printf("TESTdec1:%d\n", ft_printf("Hola %d", 42));
	printf("TESTdec1:%d\n", printf("Hola %d", 42));
	printf("TESTdec1:%d\n", ft_printf("Hola %d", -42424));
	printf("TESTdec1:%d\n", printf("Hola %d", -42424));
	printf("TESTdec1:%d\n", ft_printf("Hola %x", 42));
	printf("TESTdec1:%d\n", printf("Hola %x", 42));
	printf("TESTdec1:%d\n", ft_printf("Hola %x", -42));
	printf("TESTdec1:%d\n", printf("Hola %x", -42));
	printf("TESTdec1:%d\n", ft_printf("Hola %x", 0));
	printf("TESTdec1:%d\n", printf("Hola %x", 0));
	printf("TESTdec1:%d\n", ft_printf("Hola %s %s %d %d %x %x", "Mundo", NULL, 42, -42, 42, -42));
	printf("TESTdec1:%d\n", printf("Hola %s %s %d %d %x %x", "Mundo", NULL, 42, -42, 42, -42));
	system("leaks a.out");
	return 0;
}

int	print_str(char *str, int free_flag)
{
	int i = 0;
	if (!str)
		str = "(null)";

	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	if (free_flag)
	{
		free(str);
	}
	return (i);

}

int	ft_strlen(char *str)
{
	int i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		i++;	
	}
	return (i);
}

void	mirror_array(char *str)
{
	char swap;
	int	size;
	int	i = 0;
	int j;
	
	size = ft_strlen(str);
	while (i < size / 2)
	{
		j = size - 1 - i;
		swap = str[i];
		str[i] = str[j];
		str[j] = swap;
		i++;
	}
	return ;
}

char	*ft_itoa_base(long int nbr, char *base)
{
	char *res;
	int	i = 0;
	int neg_flag = 0;

	res = (char *)malloc(50);
	while (i < 50)
		res[i++] = 0;
	i = 0;
	if (nbr == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (nbr < 0)
	{
		nbr *= -1;
		neg_flag = 1;
	}
////	printf("ESTAMOS itoabase %ld\n", nbr);
	while (nbr > 0)
	{
		res[i] = base[nbr % ft_strlen(base)];
		nbr /= ft_strlen(base);
		i++;
	}
//	printf("ESTAMOS itoabase %s\n", res);
	if (neg_flag == 1)
		res[i] = '-';
	mirror_array(res);
//	printf("ESTAMOS itoabase final %s\n", res);
	return (res);
}

int	print_line(char *str, va_list *args)
{
	int i = 0;
	int	res = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 's')
			{
				res += print_str(va_arg(*args, char *), 0);
			}
			if (str[i] == 'd')
			{
				res += print_str(ft_itoa_base(va_arg(*args, int), "0123456789"), 1);

			}
			if (str[i] == 'x')
			{
				res += print_str(ft_itoa_base(va_arg(*args, unsigned int), "0123456789abcdef"), 1);
			}
			if (str[i] == '%')
			{
				res += print_str("%", 0);
			}
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			res++;
			i++;
		}
	}
	return (res);
}

int	ft_printf(char *str, ...)
{
	va_list args;
	int		res;

	res = 0;
	va_start(args, str);
	res = print_line(str, &args);
	va_end(args);
	return (res);
}


