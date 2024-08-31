/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:51:00 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/15 13:32:43 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleeping(t_monitor *monitor)
{
	print_msg(monitor, "is sleeping");
	ft_msleep(monitor->info->time_to_sleep);
}

void	thinking(t_monitor *monitor)
{
	print_msg(monitor, "is thinking");
	usleep(100);
}

uint64_t	cur_millisec(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
}

void	free_and_kill_all(t_monitor *monitor)
{
	uint64_t	i;

	ft_msleep(100);
	i = 0;
	while (i < monitor->info->philo_num)
	{
		kill(monitor->pid_arr[i], SIGKILL);
		sem_close(monitor->eat_time_sem[i]);
		i++;
	}
	sem_close(monitor->fork_sem);
	sem_close(monitor->print_sem);
	free(monitor->pid_arr);
	free(monitor->eat_time_sem);
}
