/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   est_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:57:26 by zchia             #+#    #+#             */
/*   Updated: 2024/08/07 13:57:26 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_log(t_philo *phi, char *status)
{
	printf("%d %d %s\n", get_time() - phi->param->begin_time,
		phi->phi_id + 1, status);
}

void	*monitor_philo(void *arg)
{
	t_philo	*phi;
	int		hungry;

	phi = (t_philo *)arg;
	while (1)
	{
		hungry = get_time() - phi->start_eat;
		if (hungry > phi->param->rules.t_die)
		{
			print_log(phi, "died");
			exit(0);
		}
		usleep(100);
	}
	return (NULL);
}

void	eat(t_philo *phi)
{
	sem_wait(phi->param->forks);
	print_log(phi, "has taken a fork");
	sem_wait(phi->param->forks);
	print_log(phi, "has taken a fork");
	phi->start_eat = get_time();
	print_log(phi, "is eating");
	usleep(phi->param->rules.t_eat * 1000);
	phi->nbr_eaten++;
	if (phi->nbr_eaten == phi->param->rules.nbr_eat)
		phi->is_full = 1;
	sem_post(phi->param->forks);
	sem_post(phi->param->forks);
}

void	*est_actions(void *arg)
{
	t_philo		*phi;
	pthread_t	monitor_thread;

	phi = (t_philo *)arg;
	if (pthread_create(&monitor_thread, NULL, monitor_philo, (void *)phi) != 0)
		return (NULL);
	pthread_detach(monitor_thread);
	while (!phi->is_full)
	{
		eat(phi);
		print_log(phi, "is sleeping");
		usleep(phi->param->rules.t_sleep * 1000);
		if (phi->is_full)
			exit(0);
		print_log(phi, "is thinking");
	}
	exit(0);
	return (NULL);
}
