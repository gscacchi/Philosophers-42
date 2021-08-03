/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:45:19 by gscala            #+#    #+#             */
/*   Updated: 2021/08/02 17:45:34 by gscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    ft_think(t_philo *philo)
{
    ft_print_all(philo, 't');
}

void    ft_sleep(t_philo *philo)
{
	ft_print_all(philo, 's');
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void    ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->t_mutex->mutex[philo->indice]);
	ft_print_all(philo, 'l');
	if (philo->indice != philo->data->number_of_philosophers - 1)
		pthread_mutex_lock(&philo->t_mutex->mutex[philo->indice + 1]);
	else
		pthread_mutex_lock(&philo->t_mutex->mutex[0]);
	ft_print_all(philo, 'r');
	ft_print_all(philo, 'e');
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->t_mutex->mutex[philo->indice]);
	if (philo->indice != philo->data->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->t_mutex->mutex[philo->indice + 1]);
	else
		pthread_mutex_unlock(&philo->t_mutex->mutex[0]);
}

void    *ft_routine(void *argp)
{
	t_philo *philo;
	philo = (t_philo *)argp;
	pthread_mutex_lock(&philo->t_mutex->mutex_stampa);
	while (1)
	{
		if (ft_end_eating(philo) == 1)
			ft_print_all(philo, 'q');
		ft_eating(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	pthread_mutex_unlock(&philo->t_mutex->mutex_stampa);
	return(NULL);
}
