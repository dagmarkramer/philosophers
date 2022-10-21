/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagmarkramer <dagmarkramer@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:56:47 by dkramer           #+#    #+#             */
/*   Updated: 2022/10/20 14:56:09 by dagmarkrame      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_philo(t_phi_thread *phi_thread)
{
	if (phi_thread->phi->nr_of_phi == 1)
	{
		if (pthread_mutex_lock(&phi_thread->phi->forks[0]) != 0)
			return (returnft());
		if (ft_print_with_lock(phi_thread, "has taken a fork",
				phi_thread->begin_time, 0) != 0)
			return (1);
		if (usleep(phi_thread->phi->time_to_die * 1000) != 0)
			return (returnft());
		if (ft_print_with_lock(phi_thread, "died", phi_thread->begin_time,
				1) != 0)
			return (1);
		if (pthread_mutex_unlock(&phi_thread->phi->forks[0]) != 0)
			return (returnft());
		return (1);
	}
	return (0);
}

void	*philo_thread(void *phi)
{
	t_phi_thread	*phi_thread;

	phi_thread = (t_phi_thread *)phi;
	if (one_philo(phi_thread) != 0)
		return (NULL);
	while (1)
	{
		if (check_dead(phi_thread, phi_thread->begin_time,
				phi_thread->begin_last_meal, phi_thread->cpy_begin_l_m) == 1)
			break ;
		if (take_forks(phi_thread) == 1)
			break ;
		if (eat_and_put_down_forks(phi_thread) == 1)
			break ;
		if (ft_print_with_lock(phi_thread, "is sleeping",
				phi_thread->begin_time, 0) != 0)
			break ;
		ft_sleep(phi_thread, 2);
		if (ft_print_with_lock(phi_thread, "is thinking",
				phi_thread->begin_time, 0) != 0)
			break ;
	}
	return (NULL);
}

int	join_threads(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < phi->nr_of_phi)
	{
		if (pthread_join(phi->t[i], NULL))
			return (returnft());
		i++;
	}
	return (0);
}
