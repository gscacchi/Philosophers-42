/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:17:22 by gscala            #+#    #+#             */
/*   Updated: 2021/08/02 17:17:26 by gscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//time of death must be right

#include "philosophers.h"

int	ft_check_arguments(int argc, char **argv)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	if (argc < 5 || argc > 6)
		return(0);
	while (argv[i])
	{
		k = 0;
		while (argv[i][k])
		{
			if (argv[i][k] >= '0' && argv[i][k] <= '9')
				k++;
			else
				return(0);
		}
		i++;
	}
	return(1);
}

void	ft_parsing(t_data *data, int argc, char **argv)
{
	if (ft_check_arguments(argc, &(*argv)) != 1)
	{
		printf("Invalid arguments\n");
		exit(0);
	}
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	else
		data->times_must_eat = 0;

}

void 	ft_init(t_philo *philo, t_mutex *mutex, t_data *data, int n)
{
	u_int64_t i;

	i = 0;
	while (i < (u_int64_t)n)
	{
		pthread_mutex_init(&mutex->mutex[i], NULL);
		philo[i].data = data;
        philo[i].time_has_eaten = 0;
        i++;
	}
	i = 0;
	while (i < (u_int64_t)n)
	{
		philo[i].t_mutex = mutex;
		philo[i].indice = i;
		pthread_create(&philo[i].philosopher, NULL, &ft_routine, &philo[i]);
		pthread_create(&philo[i].check, NULL, &ft_check_if_dead, &philo[i]);
		usleep(5);
		i += 2;
	}
	i = 1;
	while (i < (u_int64_t)n)
    {   
    	philo[i].t_mutex = mutex;
    	philo[i].indice = i;
    	pthread_create(&philo[i].philosopher, NULL, &ft_routine, &philo[i]);
		pthread_create(&philo[i].check, NULL, &ft_check_if_dead, &philo[i]);
		usleep(5);
		i += 2;
	}
	i = 0;
	while (i < (u_int64_t)n)
	{
		pthread_join(philo[i].philosopher, NULL);
		pthread_join(philo[i].check, NULL);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_data 		data;
	u_int64_t 	i;
	t_philo 	*philo;
	t_mutex 	mutex;

	i = 0;
	mutex.mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	data.start = ft_get_time();
	data.have_eaten = 0;
	ft_parsing(&data, argc, &(*argv));
	pthread_mutex_init(&mutex.mutex_stampa, NULL);
	ft_init(philo, &mutex, &data, ft_atoi(argv[1]));
	while (i < (uint64_t)data.number_of_philosophers)
	{
		pthread_mutex_destroy(&mutex.mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->t_mutex->mutex_stampa);
	return(1);
}