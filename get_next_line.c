/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoaoki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 03:35:01 by yoaoki            #+#    #+#             */
/*   Updated: 2024/05/22 04:07:39 by yoaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // for read
#include <stdlib.h> // for malloc, free

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

typedef struct s_line
{
	char *str;
	size_t len;
	size_t capa;
} t_line;

char ft_getc(int fd)
{
	static char buff[BUFFER_SIZE];
	static char *buffptr;
	static int read_byte;

	if (read_byte == 0)
	{
		read_byte = read(fd, buff, BUFFER_SIZE);
		buffptr = buff;
	}
	return ((--read_byte >= 0) ? (*buffptr++) : -5);
}

void ft_putc(t_line *line, char c)
{
	char  *new_str;

	if (line->len + 1 >= line->capa)
	{
		line->capa = (line->len + 1) * 2;
		new_str = (char *)malloc(sizeof(char) * line->capa);
		size_t len = line->len;
		char *src = line->str;
		char *dest = new_str;
		while (len--)
			*dest++ = *src++;
		free(line->str);
		line->str = new_str;
	}
	line->str[line->len++] = c;
}

char *get_next_line(int fd)
{
	char c;
	t_line line;

	line.str = 0;
	line.len = 0;
	line.capa = 0;
	while (1)
	{
		c = ft_getc(fd);
		if (c == -5)
			break;
		ft_putc(&line, c);
		if (c == '\n')
			break;
	}
	if(line.len > 0)
		ft_putc(&line, 0);
	return (line.str);
}


#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	char *line;
	int fd = open("ft_printf.c", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
