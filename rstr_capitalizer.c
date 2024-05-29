/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rstr_capitalizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoaoki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:24:14 by yoaoki            #+#    #+#             */
/*   Updated: 2024/05/22 02:27:09 by yoaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int is_upper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

int is_lower(char c)
{
	return (c >= 'a' && c <= 'z');
}

void	to_upper(char *c)
{
	*c -= 'a' - 'A';
}

void	to_lower(char *c)
{
	*c += 'a' - 'A';
}


void	str_capitalizer(char *str)
{
	while (*str)
	{
		if (is_lower(*str) && (*(str + 1) == '\0' || *(str + 1) == ' ' || *(str + 1) == '\t'))
			to_upper(str);
		else if (is_upper(*str) && *(str + 1) && *(str + 1) != ' ' && *(str + 1) != '\t')
			to_lower(str);
		write(1, str, 1);
		str++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	int i = 1;
	while (i < argc)
	{
		str_capitalizer(argv[i]);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
