#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef	struct 	s_mutex{
	pthread_mutex_t		*mutex;
	pthread_mutex_t		mutex_stampa;
}				t_mutex;

typedef	struct 	s_data{
	u_int64_t	number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_must_eat;
	u_int64_t	start;
}				t_data;

typedef	struct	s_philo{
	pthread_t	philosopher;
	int			indice;
	int			time_has_eaten;
	struct s_data	*data;
	struct s_mutex	*t_mutex;
	pthread_t	check;
}				t_philo;

int		ft_atoi(char *str);
void	ft_print_all(t_philo *philo, char c);
void 	*ft_check_if_dead(void *argp);
void    ft_think(t_philo *philo);
void    ft_sleep(t_philo *philo);
void    ft_eating(t_philo *philo);
void    *ft_routine(void *argp);
uint64_t	ft_get_time(void);
void	ft_usleep(int time, t_data *data);


#endif
