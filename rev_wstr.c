/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoaoki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:31:52 by yoaoki            #+#    #+#             */
/*   Updated: 2024/05/22 03:17:22 by yoaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // for write
#include <stdlib.h> // for malloc, free

/*
 * Write a program that takes a string as a parameter, and prints its words in reverse order.
 * A "word" is a part of the string bounded by spaces and/or tabs, or the begin/end of the string.
 * If the number of parameters is different from 1, the program will display "\n".
 *
 * In the parameters that are going to be tested, there won't be any "additional" spaces (
 * meaning that there won't be additionaal spaces at the beginning or at
 * the end of the string, and words will alwayas be separated by exactly one space).
 *
 */
int ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
// 単語を
int	count_words(char *str)
{
	int count;
	int in_words;

	count = 0;
	in_words = 0;
	while (*str)
	{
		if (in_words == 0 && !ft_isspace(*str))
		{
			in_words = 1;
			count++;
		}
		else if (in_words && ft_isspace(*str))
			in_words = 0;
		str++;
	}
	return (count);
}

int ft_strsplen(char *str)
{
	int len = 0;
	while (str[len] && !ft_isspace(str[len]))
		len++;
	return (len);
}

int ft_strlcpy(char *dest, char *src, int len)
{
	if (len == 0)
	{
		return (0);
	}
	while (*src && len - 1)
	{
		*dest++ = *src++;
		len--;
	}
	*dest = '\0';
	return (1);
}

char **ft_split(char *str)
{
	int len = count_words(str);
	char **result = (char **)malloc(sizeof(char *) * (len + 1));
	if (!result)
		return ((void *)0);
	int i = 0;
	while (i < len)
	{
		while (ft_isspace(*str))
			str++;
		int splitlen = ft_strsplen(str);
		result[i] = (char *)malloc(sizeof(char) * (splitlen + 1));
		// really this need free if error
		ft_strlcpy(result[i], str, splitlen + 1);
		while (!ft_isspace(*str))
			str++;
		i++;
	}
	result[i] = (void *)0;
	return (result);
}

int ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void 	ft_putstr(char *str)
{
	int len = ft_strlen(str);
	write(1, str, len);
}


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	int len = count_words(argv[1]);
	char **split = ft_split(argv[1]);
	for (int i = len - 1; i >= 0; i--)
	{
		ft_putstr(split[i]);
		if (i != 0)
			write(1, " ", 1);
		else if (i == 0)
			write(1, "\n", 1);
		free (split[i]);
	}
	free(split);
	return (0);
}
