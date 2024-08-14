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

#include "philo.h"

int	ft_isint(const char *str)
{
	int	nbr;

	nbr = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = 1;
		str++;
	}
	while (*str == ' ' || *str == '\t')
		str++;
	return (nbr && *str == '\0');
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_log(t_philo *phi, char *status)
{
	pthread_mutex_lock(&phi->param->print_mutex);
	if (!phi->param->stop)
		printf("%d %d %s\n", get_time() - phi->param->begin_time,
			phi->phi_id, status);
	pthread_mutex_unlock(&phi->param->print_mutex);
}

void	eat(t_philo *phi, t_fork *forks)
{
	int	first_fork;
	int	second_fork;

	first_fork = phi->phi_id;
	second_fork = (phi->phi_id + 1) % phi->param->rules.nbr_phi;
	if (!(phi->phi_id % 2))
	{
		first_fork = (phi->phi_id + 1) % phi->param->rules.nbr_phi;
		second_fork = phi->phi_id;
	}
	pthread_mutex_lock(&forks[first_fork].fork_mutex);
	print_log(phi, "has taken a fork");
	pthread_mutex_lock(&forks[second_fork].fork_mutex);
	print_log(phi, "has taken a fork");
	pthread_mutex_lock(&phi->eat_mutex);
	print_log(phi, "is eating");
	pthread_mutex_lock(&phi->die_mutex);
	phi->start_time = get_time();
	pthread_mutex_unlock(&phi->die_mutex);
	usleep(phi->param->rules.t_eat * 1000);
	phi->nbr_eaten++;
	pthread_mutex_unlock(&phi->eat_mutex);
	pthread_mutex_unlock(&forks[second_fork].fork_mutex);
	pthread_mutex_unlock(&forks[first_fork].fork_mutex);
}

void	*est_actions(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	if (phi->param->rules.nbr_phi == 1)
	{
		print_log(phi, "has taken a fork");
		usleep(phi->param->rules.t_die * 1000);
		return (NULL);
	}
	while (!phi->param->stop)
	{
		if (phi->nbr_eaten < phi->param->rules.nbr_eat)
		{
			eat(phi, phi->param->forks);
			print_log(phi, "is sleeping");
			usleep(phi->param->rules.t_sleep * 1000);
			print_log(phi, "is thinking");
		}
	}
	return (NULL);
}
