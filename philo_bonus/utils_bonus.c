/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:56:39 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/15 14:51:17 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_msleep(uint64_t ms)
{
	uint64_t	dest_ms;

	dest_ms = cur_millisec() + ms;
	while (cur_millisec() < dest_ms)
		usleep(100);
}

void	print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

void	sem_open_and_unlink(sem_t **sem, uint64_t sem_value)
{
	*sem = sem_open(SEM_NAME, O_CREAT, S_IRWXU, sem_value);
	sem_unlink(SEM_NAME);
}

void	print_msg(t_monitor *monitor, char *msg)
{
	sem_wait(monitor->print_sem);
	printf("%lu %lu %s\n", cur_millisec() - monitor->start_time,
		monitor->philo_idx + 1, msg);
	sem_post(monitor->print_sem);
}
