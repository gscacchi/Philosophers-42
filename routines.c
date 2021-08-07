/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 16:09:35 by gscala            #+#    #+#             */
/*   Updated: 2021/08/07 16:09:36 by gscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_think(t_philo *philo)
{
	ft_print_all2(philo, 't');
}

void	ft_sleep(t_philo *philo)
{
	ft_print_all(philo, 's');
	ft_usleep(philo->data->time_to_sleep);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->t_mutex->mutex[philo->indice]);
	ft_print_all(philo, 'l');
	if (philo->indice != philo->data->number_of_philosophers - 1)
		pthread_mutex_lock(&philo->t_mutex->mutex[philo->indice + 1]);
	else
		pthread_mutex_lock(&philo->t_mutex->mutex[0]);
	ft_print_all(philo, 'r');
	ft_print_all2(philo, 'e');
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->t_mutex->mutex[philo->indice]);
	if (philo->indice != philo->data->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->t_mutex->mutex[philo->indice + 1]);
	else
		pthread_mutex_unlock(&philo->t_mutex->mutex[0]);
}

void	*ft_routine(void *argp)
{
	t_philo	*philo;

	philo = (t_philo *)argp;
	while (1)
	{
		if (ft_end_eating(philo) == 1)
			ft_print_all2(philo, 'q');
		ft_eating(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
