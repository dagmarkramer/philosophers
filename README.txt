INTRODUCTION
------------

this is a program which makes use of mulithreading

the goal is to let 'philosophers' alternatively eat, sleep, or think

each philosopher is a thread and there are as many forks as philosophers

each philosopher needs two forks to eat so they can't eat at the same time

to keep philosophers from stealing each other's forks, mutexes are used


UTILISATION
------------

run 'make'

run './philo [nr_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [opt. times_each_philo_must_eat]'

ex: ./philo 20 600 200 200
