/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dagmarkramer <dagmarkramer@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:56:33 by dkramer       #+#    #+#                 */
/*   Updated: 2022/10/21 13:54:22 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	new_time(void)
{
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL) != 0)
		return (returnft());
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

int	free_when_error(t_phi *phi)
{
	if (!phi->t)
	{
		free (phi->forks);
		free (phi->fork_taken);
		return (returnft());
	}
	if (!phi->forks)
	{
		free (phi->t);
		free (phi->fork_taken);
		return (returnft());
	}
	if (!phi->fork_taken)
	{
		free (phi->t);
		free (phi->forks);
		return (returnft());
	}
	return (0);
}

int	ft_print_with_lock(t_phi_thread *phi_thread, char *print_string,
		long int begin_time, int die)
{
	long int	time_now;

	time_now = new_time();
	if (time_now == 1)
		return (1);
	if (pthread_mutex_lock(&phi_thread->phi->died_lock) != 0)
		return (returnft());
	if (phi_thread->phi->philo_die == 0)
		printf("%ld %d %s\n", time_now - begin_time, phi_thread->philo,
			print_string);
	if (die == 1)
		phi_thread->phi->philo_die = 1;
	if (pthread_mutex_unlock(&phi_thread->phi->died_lock) != 0)
		return (returnft());
	return (0);
}

int	check_dead(t_phi_thread *phi_thread, long int begin_time,
		long int begin_l_m, long int copy_b_l_m)
{
	int				returny;
	const long int	time_now = new_time();

	returny = 0;
	if (pthread_mutex_lock(&phi_thread->phi->died_lock) != 0)
		return (returnft());
	if (phi_thread->phi->philo_die == 1)
		returny = 1;
	if (pthread_mutex_unlock(&phi_thread->phi->died_lock) != 0)
		return (returnft());
	if (returny == 1 || time_now == 1)
		return (1);
	if ((begin_l_m - copy_b_l_m > phi_thread->phi->time_to_die && begin_l_m != 0
			&& copy_b_l_m != 0) || (time_now - begin_time
			> phi_thread->phi->time_to_die && begin_l_m == 0)
		|| (time_now - begin_l_m > phi_thread->phi->time_to_die
			&& begin_l_m != 0))
	{
		ft_print_with_lock(phi_thread, "died", begin_time, 1);
		returny = 1;
	}
	return (returny);
}

int	ft_sleep(t_phi_thread *phi_thread, int eat_or_sleep)
{
	long int	time;
	long int	begin;

	if (eat_or_sleep == 1)
		time = phi_thread->phi->time_to_eat;
	else if (eat_or_sleep == 2)
		time = phi_thread->phi->time_to_sleep;
	begin = new_time();
	if (begin == 1)
		return (1);
	while (new_time() - begin < time)
	{
		if (check_dead(phi_thread, phi_thread->begin_time,
				phi_thread->begin_last_meal, phi_thread->cpy_begin_l_m) == 1)
			return (1);
		if (usleep(250) != 0)
			return (returnft());
	}
	return (0);
}
