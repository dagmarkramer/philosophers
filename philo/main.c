/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dagmarkramer <dagmarkramer@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:56:27 by dkramer       #+#    #+#                 */
/*   Updated: 2022/10/21 13:56:16 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_phi *phi, t_phi_thread *phi_thread)
{
	int	i;
	int	ret;

	i = 0;
	while (i < phi->nr_of_phi)
	{
		if ((i + 1) % 2 == 0)
			usleep(500);
		ret = pthread_create(&phi->t[i], NULL, philo_thread, &phi_thread[i]);
		if (ret)
			return (returnft());
		i++;
	}
	return (ret);
}

int	philo_loop(t_phi *phi)
{
	int				i;
	t_phi_thread	*phi_thread;
	int				ret;

	phi_thread = ft_calloc(1, sizeof(t_phi_thread) * (phi->nr_of_phi));
	if (!phi_thread)
		return (returnft());
	i = 0;
	while (i < phi->nr_of_phi)
	{
		phi_thread[i].philo = i + 1;
		phi_thread[i].phi = phi;
		phi_thread[i].begin_last_meal = 0;
		phi_thread[i].cpy_begin_l_m = 0;
		phi_thread[i].begin_time = new_time();
		phi_thread[i].times_eaten = 0;
		phi_thread[i].cpy_begin_l_m = phi_thread[i].begin_time;
		i++;
	}
	ret = create_threads(phi, phi_thread);
	ret = join_threads(phi);
	free(phi_thread);
	return (ret);
}

int	init_mutexes(t_phi *phi)
{
	int	i;

	i = 0;
	phi->t = ft_calloc(1, sizeof(pthread_t) * (phi->nr_of_phi + 1));
	phi->forks = ft_calloc(1, sizeof(pthread_mutex_t) * phi->nr_of_phi);
	phi->fork_taken = ft_calloc(1, sizeof(bool) * phi->nr_of_phi);
	if (free_when_error(phi) == 1)
		return (1);
	while (i < phi->nr_of_phi)
	{
		if (pthread_mutex_init(&phi->forks[i], NULL) != 0)
			return (returnft());
		phi->fork_taken[i] = false;
		i++;
	}
	if (pthread_mutex_init(&phi->died_lock, NULL) != 0)
		return (returnft());
	if (pthread_mutex_lock(&phi->died_lock) != 0)
		return (returnft());
	phi->philo_die = 0;
	if (pthread_mutex_unlock(&phi->died_lock) != 0)
		return (returnft());
	return (0);
}

int	destroy_mutexes(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < phi->nr_of_phi)
	{
		if (pthread_mutex_destroy(&phi->forks[i]) != 0)
			return (returnft());
		i++;
	}
	if (pthread_mutex_destroy(&phi->died_lock) != 0)
		return (returnft());
	free(phi->forks);
	free(phi->t);
	free(phi->fork_taken);
	return (0);
}

int	main(int argc, char **argv)
{
	t_phi	phi;
	int		ret;

	if (errors(argv, argc, &phi) == 1)
		return (1);
	if (argc == 6 || argc == 5)
	{
		phi.nr_of_phi = ft_specatoi(argv[1], &phi);
		phi.time_to_die = ft_specatoi(argv[2], &phi);
		phi.time_to_eat = ft_specatoi(argv[3], &phi);
		phi.time_to_sleep = ft_specatoi(argv[4], &phi);
		if (argc == 6)
			phi.nr_o_t_e_phi_m_eat = ft_specatoi(argv[5], &phi);
		ret = init_mutexes(&phi);
		if (ret == 0)
		{
			ret = philo_loop(&phi);
			ret = destroy_mutexes(&phi);
		}
		return (ret);
	}
	printf("Error\n incorrect amount of arguments\n");
	return (1);
}
