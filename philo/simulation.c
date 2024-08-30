/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:39:50 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/15 21:13:27 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_two_forks_and_eat(t_simul *simul)
{
	if (simul->philo_idx % 2 == 0)
		take_two_forks_even(simul);
	else
	{
		usleep(10);
		take_two_forks_odd(simul);
	}
}

void	sleeping(t_simul *simul)
{
	print_msg(simul, "is sleeping");
	ft_msleep(simul->info->time_to_sleep);
}

void	thinking(t_simul *simul)
{
	print_msg(simul, "is thinking");
	usleep(200);
}

void	*simulation(void *arg)
{
	uint64_t	eat_time;
	t_simul		*simul;

	simul = (t_simul *)arg;
	eat_time = 0;
	while (1)
	{
		if (eat_time == simul->info->must_eat_time)
		{
			pthread_mutex_lock(simul->print_mutex);
			simul->have_eaten_the_times = 1;
			pthread_mutex_unlock(simul->print_mutex);
			break ;
		}
		take_two_forks_and_eat(simul);
		eat_time++;
		sleeping(simul);
		thinking(simul);
	}
	return (NULL);
}

void	start_simulation(t_monitor *monitor, t_info *info)
{
	uint64_t	i;
	pthread_t	th;
	uint64_t	start_time;

	i = -1;
	start_time = cur_millisec();
	while (++i < info->philo_num)
	{
		monitor->simul[i].fork = 0;
		monitor->simul[i].philo_idx = i;
		monitor->simul[i].info = monitor->info;
		monitor->simul[i].start_time = start_time;
		monitor->simul[i].last_eat_time = start_time;
		monitor->simul[i].print_mutex = &monitor->print_mutex;
		monitor->simul[i].eat_time_mutex = &monitor->eat_time_mutex[i];
		monitor->simul[i].left_fork_mutex
			= &monitor->fork_mutex[left_fork_idx(&monitor->simul[i])];
		monitor->simul[i].right_fork_mutex
			= &monitor->fork_mutex[right_fork_idx(&monitor->simul[i])];
		monitor->simul[i].have_eaten_the_times = 0;
		pthread_mutex_init(&monitor->fork_mutex[i], NULL);
		pthread_mutex_init(&monitor->eat_time_mutex[i], NULL);
		pthread_create(&th, NULL, simulation, &monitor->simul[i]);
		pthread_detach(th);
	}
}
