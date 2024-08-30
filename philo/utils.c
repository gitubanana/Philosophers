/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:37:27 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/15 10:49:18 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_msleep(uint64_t ms)
{
	uint64_t	dest_ms;

	dest_ms = cur_millisec() + ms;
	while (cur_millisec() < dest_ms)
		usleep(100);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	print_msg(t_simul *simul, char *msg)
{
	pthread_mutex_lock(simul->print_mutex);
	printf("%lu %lu %s\n", cur_millisec() - simul->start_time,
		simul->philo_idx + 1, msg);
	pthread_mutex_unlock(simul->print_mutex);
}

void	print_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

void	free_all(t_monitor *monitor)
{
	uint64_t	i;

	ft_msleep(100);
	i = 0;
	while (i < monitor->info->philo_num)
	{
		pthread_mutex_destroy(&monitor->fork_mutex[i]);
		pthread_mutex_destroy(&monitor->eat_time_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&monitor->print_mutex);
	free(monitor->simul);
	free(monitor->fork_mutex);
	free(monitor->eat_time_mutex);
}
