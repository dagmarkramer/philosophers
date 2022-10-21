/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagmarkramer <dagmarkramer@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:22:27 by dagmarkrame       #+#    #+#             */
/*   Updated: 2022/10/20 14:57:30 by dagmarkrame      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	try_take_fork(t_phi_thread *phi_thread, int i)
{
	while (1)
	{
		if (pthread_mutex_lock(&phi_thread->phi->forks[i]) != 0)
			return (returnft());
		if (phi_thread->phi->fork_taken[i] == false)
		{
			phi_thread->phi->fork_taken[i] = true;
			if (ft_print_with_lock(phi_thread, "has taken a fork",
					phi_thread->begin_time, 0) != 0)
				return (1);
			if (pthread_mutex_unlock(&phi_thread->phi->forks[i]) != 0)
				return (returnft());
			break ;
		}
		else
		{
			if (pthread_mutex_unlock(&phi_thread->phi->forks[i]) != 0)
				return (returnft());
		}
		if (check_dead(phi_thread, phi_thread->begin_time,
				phi_thread->begin_last_meal, phi_thread->cpy_begin_l_m) == 1)
			return (1);
		usleep(500);
	}
	return (0);
}

int	put_down_fork(t_phi_thread *phi_thread, int i)
{
	if (pthread_mutex_lock(&phi_thread->phi->forks[i]) != 0)
		return (returnft());
	phi_thread->phi->fork_taken[i] = false;
	if (pthread_mutex_unlock(&phi_thread->phi->forks[i]) != 0)
		return (returnft());
	return (0);
}

int	take_forks(t_phi_thread *phi_thread)
{
	if (try_take_fork(phi_thread, phi_thread->philo - 1) == 1)
		return (1);
	if (phi_thread->philo == phi_thread->phi->nr_of_phi)
	{
		if (try_take_fork(phi_thread, 0) == 1)
			return (1);
	}
	else
	{
		if (try_take_fork(phi_thread, phi_thread->philo) == 1)
			return (1);
	}
	return (0);
}

int	eat_and_put_down_forks(t_phi_thread *phi_thread)
{
	phi_thread->begin_last_meal = new_time();
	if (phi_thread->begin_last_meal == 1)
		return (1);
	if (ft_print_with_lock(phi_thread, "is eating", phi_thread->begin_time,
			0) != 0)
		return (1);
	ft_sleep(phi_thread, 1);
	phi_thread->cpy_begin_l_m = phi_thread->begin_last_meal;
	if (phi_thread->philo == phi_thread->phi->nr_of_phi)
	{
		if (put_down_fork(phi_thread, 0) == 1)
			return (1);
	}
	else
	{
		if (put_down_fork(phi_thread, phi_thread->philo) == 1)
			return (1);
	}
	if (put_down_fork(phi_thread, phi_thread->philo - 1) == 1)
		return (1);
	phi_thread->times_eaten++;
	if (phi_thread->times_eaten == phi_thread->phi->nr_o_t_e_phi_m_eat)
		return (1);
	return (0);
}
