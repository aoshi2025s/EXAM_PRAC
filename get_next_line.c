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

#ifndef EOF
# define EOF -42
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
	read_byte--;
	if (read_byte >= 0)
		return (*(buffptr++));
	return (EOF);
}

char *ft_memcpy(void *dest, void *src, size_t len)
{
	unsigned char *d = (unsigned char *)dest;
	unsigned char *s = (unsigned char *)src;
	while (len)
	{
		*d++ = *s++;
		len--;
	}
	return ((char *)dest);
}

int ft_putc(t_line *line, char c)
{
	char  *new_str;
	char *delete_str;
	if (line->len + 1 > line->capa)
	{
		new_str = (char *)malloc(sizeof(char) * ((line->len + 1) * 2));
		ft_memcpy(new_str, line->str, line->len);
		delete_str = line->str;
		line->str = new_str;
		free (delete_str);
		line->capa = (line->len + 1) * 2;
	}
	line->str[line->len] = c;
	line->len++;
	return (1);
}

char *get_next_line(int fd)
{
	char c;
	t_line line;

	line.str = (void *)0;
	line.len = 0;
	line.capa = 0;


	if (fd < 0 || BUFFER_SIZE < 0) 
		return ((void *)0);
	while (1)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break;
		ft_putc(&line, c);
		if (c == '\n')
			break;
	}
	if(line.len > 0)
		ft_putc(&line, '\0');
	return (line.str);
}

/*
#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	char *line;
	int fd = open("test.txt", O_RDONLY);
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
*/
