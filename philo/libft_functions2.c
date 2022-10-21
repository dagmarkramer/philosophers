/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagmarkramer <dagmarkramer@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:23:18 by dkramer           #+#    #+#             */
/*   Updated: 2022/10/20 14:53:17 by dagmarkrame      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*ptr;
	unsigned long	i;
	void			*ptr1;

	i = 0;
	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		while (i < (count * size))
		{
			ptr[i] = '\0';
			i++;
		}
	}
	ptr1 = (void *)ptr;
	return (ptr1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	c1;

	c1 = (char)c;
	i = ft_strlen(s);
	while (*s)
		s++;
	while (i >= 0)
	{
		if (*s == c1)
			return ((char *)s);
		i--;
		s--;
	}
	if (c1 == '\0')
		return ((char *)s);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	returnft(void)
{
	ft_putstr_fd("Error\n", 2);
	return (1);
}
