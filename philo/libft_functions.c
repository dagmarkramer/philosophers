/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagmarkramer <dagmarkramer@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:23:12 by dkramer           #+#    #+#             */
/*   Updated: 2022/10/20 14:55:42 by dagmarkrame      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	extrachecks(long long int nmb, int a)
{
	if ((nmb * a) > 2147483647)
		return (-1);
	if ((nmb * a) < -2147483648)
		return (-1);
	return (nmb * a);
}

int	ft_specatoi(const char *st, t_phi *phi)
{
	long long int	nmb;
	int				i;
	int				a;

	nmb = 0;
	i = 0;
	a = 1;
	while (((st[i] >= 9 && st[i] <= 13) || st[i] == 32) && st[i])
		i++;
	if ((st[i] == '-' || st[i] == '+') && st[i])
	{
		if (st[i] == '-')
			a = a * -1;
		i++;
	}
	if (st[i] == '-' || st[i] == '+')
		phi->extraminusorplus = 1;
	while (st[i] != '\0' && st[i] >= '0' && st[i] <= '9' && st[i])
	{
		nmb = (nmb * 10) + st[i] - 48;
		i++;
	}
	return (extrachecks(nmb, a));
}

int	noninteger(char **argv, t_phi *phi)
{
	int	i;
	int	a;

	i = 1;
	while (i < phi->argc)
	{
		a = 0;
		while (argv[i][a])
		{
			if (!ft_strrchr("-+0123456789", argv[i][a]))
				return (returnft());
			a++;
		}
		i++;
	}
	return (0);
}

int	maxint(char **argv, t_phi *phi)
{
	int	a;
	int	nr;

	a = 1;
	phi->isminusone = 0;
	phi->extraminusorplus = 0;
	while (a < phi->argc)
	{
		nr = ft_specatoi(argv[a], phi);
		if (nr == 0)
			return (returnft());
		if (nr < 0)
			return (returnft());
		if (phi->extraminusorplus == 1)
			return (returnft());
		if (nr == -1 && phi->isminusone != 1)
			return (returnft());
		a++;
	}
	return (0);
}

/* some arguments are not integers, some arguments are bigger than an integer,
there are duplicates*/
int	errors(char **argv, int argc, t_phi *phi)
{
	phi->argc = argc;
	phi->extraminusorplus = 0;
	if (noninteger(argv, phi))
		return (1);
	if (maxint(argv, phi))
		return (1);
	return (0);
}
