#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


char	*get_next_line(int fd);
char 	*add_char_to_str(char chr, char *str);

int main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	int		i = 0;
	if (argc != 2)
		return(0) ;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("LINE[%d]:\t%s", i, line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	system("leaks a.out");
	return (0);
}

char	*get_next_line(int fd)
{
	char buffer[2];
	char	*res;

	buffer[0] = 0;
	buffer[1] = 0;
	res = 0;
	while (buffer[0] != '\n' && read(fd, &buffer[0], BUFFER_SIZE*0+1) && buffer[0] != 0)
		res = add_char_to_str(buffer[0], res);
	return(res);
}

int	ft_strlen(char *str)
{
	int	i = 0;
	if (!str)
		return (-1);
	while(str[i])
		i++;
	return (i);
}

char	*add_char_to_str(char chr, char *str)
{
	int	i = 0;
	int	init_len;
	char	*swap;

	if (ft_strlen(str) == -1)
	{
		str = (char *)malloc(1);
		str[0] = 0;
	}
	init_len = ft_strlen(str);
	swap = (char *)malloc(init_len + 2);
	swap[init_len + 1] = 0;
	while(str[i] != 0)
	{
		swap[i] = str[i];
		i ++;
	}
	swap[i] = chr;
	free (str);
	str = swap;
	return (str);
}
