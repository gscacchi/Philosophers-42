/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 16:09:53 by gscala            #+#    #+#             */
/*   Updated: 2021/08/07 16:09:54 by gscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(int time)
{
	unsigned long	end;

	end = ft_get_time() + time;
	while (ft_get_time() < end)
		usleep(time);
}

uint64_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_print_all(t_philo *philo, char c)
{
	u_int64_t	end;
	uint64_t	tmilli;

	end = ft_get_time();
	tmilli = end - philo->data->start;
	pthread_mutex_lock(&philo->t_mutex->mutex_stampa);
	if (c == 's')
		printf("\e[0;37m%llu \e[0m philo %d is sleeping\n",
			tmilli, philo->indice + 1);
	if (c == 'd')
	{
		printf("Philo %d is dead\n", philo->indice + 1);
		exit(0);
	}
	if (c == 'l')
		printf("\e[1;34m%llu \e[0m philo %d has taken left fork\n",
			tmilli, philo->indice + 1);
	if (c == 'r')
		printf("\e[0;36m%llu \e[0m philo %d has taken right fork\n",
			tmilli, philo->indice + 1);
	pthread_mutex_unlock(&philo->t_mutex->mutex_stampa);
}

void	ft_print_all2(t_philo *philo, char c)
{
	u_int64_t	end;
	uint64_t	tmilli;

	end = ft_get_time();
	tmilli = end - philo->data->start;
	pthread_mutex_lock(&philo->t_mutex->mutex_stampa);
	if (c == 'e')
	{
		philo->time_has_eaten = philo->time_has_eaten + 1;
		if (philo->time_has_eaten == philo->data->times_must_eat)
			philo->data->have_eaten += 1;
		philo->moving_start = end;
		printf("\e[0;32m%llu \e[0m philo %d is eating\n",
			tmilli, philo->indice + 1);
	}
	if (c == 't')
		printf("\e[0;33m%llu \e[0m philo %d is thinking\n",
			tmilli, philo->indice + 1);
	if (c == 'q')
	{
		printf("\e[0;33m%llu \e[0m Everyone has eaten %d times\n",
			tmilli, philo->data->times_must_eat);
		exit(0);
	}
	pthread_mutex_unlock(&philo->t_mutex->mutex_stampa);
}
