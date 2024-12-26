/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalaty <sdalaty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:04:02 by sdalaty           #+#    #+#             */
/*   Updated: 2024/08/13 11:04:06 by sdalaty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_status(char **argv, t_status *status)
{
	status->total_philo = ft_atoi(argv[1]);
	status->time_of_death = ft_atoi(argv[2]);
	status->time_of_eating = ft_atoi(argv[3]);
	status->time_of_sleeping = ft_atoi(argv[4]);
	status->meals_to_eat = -1;
	if (argv[5])
		status->meals_to_eat = ft_atoi(argv[5]);
	status->meals_repeated = 0;
	status->start_time = get_current_time();
	status->stop_dinner = FALSE;
	pthread_mutex_init(&status->m_print_status, NULL);
	pthread_mutex_init(&status->m_meals_repeated, NULL);
	pthread_mutex_init(&status->m_stop_dinner, NULL);
	pthread_mutex_init(&status->m_last_meal, NULL);
}

pthread_mutex_t	*init_forks(t_status *status)
{
	pthread_mutex_t	*m_forks;
	size_t			i;

	m_forks = malloc(status->total_philo * sizeof(pthread_mutex_t));
	if (!m_forks)
		return (NULL);
	i = -1;
	while (++i < status->total_philo)
		pthread_mutex_init(&m_forks[i], NULL);
	return (m_forks);
}

t_philosopher	*init_philosophers(t_status *status, pthread_mutex_t **m_forks)
{
	t_philosopher	*philos;
	size_t			i;

	philos = malloc(status->total_philo * sizeof(t_philosopher));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < status->total_philo)
	{
		philos[i].philo_name = i + 1;
		philos[i].m_left_fork = \
			&(*m_forks)[ft_min(i, ((i + 1) % status->total_philo))];
		philos[i].m_right_fork = \
			&(*m_forks)[ft_max(i, ((i + 1) % status->total_philo))];
		philos[i].status = status;
		philos[i].eat_again = 0;
		philos[i].last_meal = status->start_time;
		i++;
	}
	return (philos);
}
