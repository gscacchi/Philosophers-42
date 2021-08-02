/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:17:45 by gscala            #+#    #+#             */
/*   Updated: 2021/08/02 17:17:46 by gscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(int time, t_data *data)
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

void    ft_print_all(t_philo *philo, char c)
{
	u_int64_t       end;
	uint64_t        tmilli;

	end = ft_get_time();
	tmilli = end - philo->data->start;

	pthread_mutex_lock(&philo->t_mutex->mutex_stampa);
    if (c == 'l')
        printf("\e[1;34m%llu \e[0m philo %d has taken left fork\n", tmilli, philo->indice + 1);
    if (c == 'r')
        printf("\e[0;36m%llu \e[0m philo %d has taken right fork\n", tmilli, philo->indice + 1);
    if (c == 'e')
    {
        //printf("Actual time %llu\n", philo->data->actual_time);
        philo->time_has_eaten = philo->time_has_eaten + 1;
        //philo->start = philo->data->actual_time;
        printf("\e[0;32m%llu \e[0m philo %d is eating\n", tmilli, philo->indice + 1);
        printf("philo %d has eaten %d times\n", philo->indice + 1, philo->time_has_eaten);
    }
    if (c == 's')
        printf("\e[0;37m%llu \e[0m philo %d is sleeping\n", tmilli, philo->indice + 1);
    if (c == 't')
        printf("\e[0;33m%llu \e[0m philo %d is thinking\n", tmilli, philo->indice + 1);
    pthread_mutex_unlock(&philo->t_mutex->mutex_stampa);
}