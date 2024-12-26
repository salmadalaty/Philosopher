/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalaty <sdalaty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:03:55 by sdalaty           #+#    #+#             */
/*   Updated: 2024/08/13 11:03:57 by sdalaty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	meals_finished(t_status *philo_status)
{
	t_bool	boolean;

	boolean = FALSE;
	pthread_mutex_lock(&philo_status->m_meals_repeated);
	if (philo_status->meals_repeated == philo_status->total_philo)
		boolean = TRUE;
	pthread_mutex_unlock(&philo_status->m_meals_repeated);
	return (boolean);
}

static t_bool	died_of_starvation(t_philosopher *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->status->m_last_meal);
	last_meal = get_current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->status->m_last_meal);
	if (last_meal > philo->status->time_of_death)
		return (TRUE);
	return (FALSE);
}

static void	raise_stop_dinner(t_status *philo_status)
{
	pthread_mutex_lock(&philo_status->m_stop_dinner);
	philo_status->stop_dinner = TRUE;
	pthread_mutex_unlock(&philo_status->m_stop_dinner);
}

void	*thread_manager(void *arg)
{
	t_philosopher	*philo;
	t_status		*status;
	size_t			count;

	philo = (t_philosopher *)arg;
	status = philo[0].status;
	while (!meals_finished(status))
	{
		count = 0;
		while (count < status->total_philo)
		{
			if (died_of_starvation(&philo[count]))
			{
				raise_stop_dinner(status);
				print_status(&philo[count], DEAD);
				return (NULL);
			}
			count++;
		}
		usleep(3000);
	}
	return (NULL);
}
