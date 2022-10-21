/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dagmarkramer <dagmarkramer@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 11:49:47 by dkramer       #+#    #+#                 */
/*   Updated: 2022/10/21 13:54:40 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_phi
{
	int				nr_of_phi;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_o_t_e_phi_m_eat;
	int				argc;
	int				isminusone;
	int				extraminusorplus;
	pthread_mutex_t	died_lock;
	pthread_t		*t;
	pthread_mutex_t	*forks;
	bool			*fork_taken;
	int				philo_die;
}					t_phi;

typedef struct s_phi_thread
{
	t_phi			*phi;
	int				philo;
	long int		begin_last_meal;
	int				times_eaten;
	long int		cpy_begin_l_m;
	long int		begin_time;
}					t_phi_thread;

int					ft_specatoi(const char *st, t_phi *phi);
int					errors(char **argv, int argc, t_phi *phi);
void				*ft_calloc(size_t count, size_t size);
int					returnft(void);
char				*ft_strrchr(const char *s, int c);
int					ft_print_with_lock(t_phi_thread *phi_thread,
						char *print_string, long int begin_time, int die);
int					ft_sleep(t_phi_thread *phi_thread, int eat_or_sleep);
void				*philo_thread(void *phi);
long int			new_time(void);
int					join_threads(t_phi *phi);
int					check_dead(t_phi_thread *phi_thread, long int begin_time,
						long int begin_l_m, long int copy_b_l_m);
int					eat_and_put_down_forks(t_phi_thread *phi_thread);
int					take_forks(t_phi_thread *phi_thread);
int					free_when_error(t_phi *phi);

#endif