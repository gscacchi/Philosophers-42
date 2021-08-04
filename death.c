#include "philosophers.h"

void	*ft_check_if_dead(void *argp)
{
	t_philo *philo;
	philo = (t_philo *)argp;

	philo->moving_start = philo->data->start;
	while (1)
	{
		ft_check_if_dead_2(philo);
		usleep(5);
	}
	return(0);
}

void 	*ft_check_if_dead_2(t_philo *philo)
{
	uint64_t end_time;
	uint64_t actual_time;

	//pthread_mutex_lock(&philo->t_mutex->mutex_stampa);
	end_time = ft_get_time();
	actual_time = end_time - philo->moving_start;
	if (actual_time > philo->data->time_to_die)
		ft_print_all(philo, 'd');
	//pthread_mutex_unlock(&philo->t_mutex->mutex_stampa);
	return(NULL);
}

int 	ft_end_eating(t_philo *philo)
{
	if (philo->data->have_eaten == philo->data->number_of_philosophers)
		return(1);
	else
		return(0);
}