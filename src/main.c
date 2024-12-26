/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalaty <sdalaty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:03:10 by sdalaty           #+#    #+#             */
/*   Updated: 2024/08/13 11:11:02 by sdalaty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_data(t_philosopher *philos, pthread_mutex_t *m_forks)
{
	size_t	i;

	i = -1;
	while (++i < philos->status->total_philo)
		pthread_mutex_destroy(&m_forks[i]);
	pthread_mutex_destroy(&philos->status->m_print_status);
	pthread_mutex_destroy(&philos->status->m_meals_repeated);
	pthread_mutex_destroy(&philos->status->m_stop_dinner);
	pthread_mutex_destroy(&philos->status->m_last_meal);
	free(m_forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*m_forks;
	t_philosopher	*philos;
	t_status		status;

	if (!is_valid_input(argc, argv))
	{
		printf(COLOR_RED "Invalid args: usage is <nbr_of_philo>(>= 1) "\
				"<time_to_die>(>= 1) <time_to_eat>(>= 1) "\
				"<time_to_sleep>(>= 1) <must_eat>(optional)." COLOR_RESET "\n" );
		return (EXIT_FAILURE);
	}
	init_status(argv, &status);
	m_forks = init_forks(&status);
	if (!m_forks)
		return (EXIT_FAILURE);
	philos = init_philosophers(&status, &m_forks);
	if (!philos)
	{
		free(m_forks);
		return (EXIT_FAILURE);
	}
	set_dinner(&status, philos);
	free_data(philos, m_forks);
	return (0);
}
