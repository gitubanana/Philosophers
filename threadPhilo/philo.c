/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:30:40 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/17 17:03:27 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_atoi(char *str, int *is_error)
{
	int	ret;

	if (*is_error)
		return (0);
	ret = 0;
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
		{
			*is_error = 1;
			return (0);
		}
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return (ret);
}

int	init_info(t_info *info, char *argv[], int has_option)
{
	int	is_error;

	is_error = 0;
	info->philo_num = philo_atoi(argv[PHILO_NUM_IDX], &is_error);
	info->time_to_die = philo_atoi(argv[TIME_TO_DIE_IDX], &is_error);
	info->time_to_eat = philo_atoi(argv[TIME_TO_EAT_IDX], &is_error);
	info->time_to_sleep = philo_atoi(argv[TIME_TO_SLEEP_IDX], &is_error);
	info->must_eat_time = ULL_MAX;
	if (has_option)
		info->must_eat_time = philo_atoi(argv[must_eat_time_IDX], &is_error);
	return (is_error);
}

int	init_monitor(t_monitor *monitor, t_info *info)
{
	monitor->simul = malloc(sizeof(t_simul) * info->philo_num);
	monitor->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	monitor->eat_time_mutex = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!monitor->simul || !monitor->fork_mutex || !monitor->eat_time_mutex)
	{
		free(monitor->simul);
		free(monitor->fork_mutex);
		free(monitor->eat_time_mutex);
		return (ERROR);
	}
	pthread_mutex_init(&monitor->print_mutex, NULL);
	monitor->info = info;
	return (0);
}

void	monitor_philo(t_info *info, t_monitor *monitor)
{
	uint64_t	i;
	uint64_t	cur_ms;

	if (info->philo_num == 0)
		return ;
	while (1)
	{
		i = 0;
		while (i < info->philo_num)
		{
			pthread_mutex_lock(&monitor->eat_time_mutex[i]);
			cur_ms = cur_millisec();
			if (cur_ms - monitor->simul[i].last_eat_time >= info->time_to_die)
			{
				pthread_mutex_lock(&monitor->print_mutex);
				if (!monitor->simul[i].have_eaten_the_times)
					printf("%lu %lu died\n",
						cur_ms - monitor->simul[i].start_time, i + 1);
				return (free_all(monitor));
			}
			pthread_mutex_unlock(&monitor->eat_time_mutex[i]);
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_info		info;
	t_monitor	monitor;

	if (argc < 5 || argc > 6)
	{
		print_error("usage: ");
		print_error(argv[0]);
		print_error(" [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (number_of_times_each_philosopher_must_eat)\n");
	}
	else
	{
		if (init_info(&info, argv, argc == 6) == ERROR)
			print_error("Error: invalid arguments\n");
		else
		{
			if (init_monitor(&monitor, &info) == ERROR)
				print_error("Error: malloc error\n");
			else
			{
				start_simulation(&monitor, &info);
				monitor_philo(&info, &monitor);
			}
		}
	}
	return (0);
}
