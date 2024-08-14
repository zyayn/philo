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

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;
	int	i;

	nbr = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nbr);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_log(t_philo *phi, char *status)
{
	sem_wait(phi->param->print_sem);
	if (!phi->param->stop)
		printf("%d %d %s\n", get_time() - phi->param->begin_time,
			phi->phi_id, status);
	sem_post(phi->param->print_sem);
}

void	*est_actions(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	if (phi->param->rules.nbr_phi == 1)
	{
		print_log(phi, "has taken a fork");
		usleep(phi->param->rules.t_die * 1000);
		exit(0);
	}
	while (!phi->param->stop && phi->nbr_eaten < phi->param->rules.nbr_eat)
	{
		sem_wait(phi->param->forks);
		print_log(phi, "has taken a fork");
		sem_wait(phi->param->forks);
		print_log(phi, "has taken a fork");
		sem_wait(phi->param->print_sem);
		phi->start_time = get_time();
		sem_post(phi->param->print_sem);
		print_log(phi, "is eating");
		usleep(phi->param->rules.t_eat * 1000);
		phi->nbr_eaten++;
		sem_post(phi->param->forks);
		sem_post(phi->param->forks);
		print_log(phi, "is sleeping");
		usleep(phi->param->rules.t_sleep * 1000);
		print_log(phi, "is thinking");
	}
	return (NULL);
}
