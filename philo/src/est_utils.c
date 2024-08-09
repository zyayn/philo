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

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_log(t_param *param, int id, char *status)
{
	pthread_mutex_lock(&param->print_mutex);
	if (!param->stop)
		ft_printf("%d %d %s\n", get_time() - param->begin_time, id, status);
	pthread_mutex_unlock(&param->print_mutex);
}

void	destroy_param(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->rules.nbr_phi)
	{
		pthread_mutex_destroy(&param->philos[i].die_mutex);
		pthread_mutex_destroy(&param->philos[i].eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&param->print_mutex);
	free(param->forks);
	free(param);
}

void	eat(t_param *param, t_philo *phi, t_fork *forks)
{
	int	first_fork;
	int	second_fork;

	first_fork = phi->phi_id;
	second_fork = (phi->phi_id + 1) % param->rules.nbr_phi;
	if (!(phi->phi_id % 2))
	{
		first_fork = (phi->phi_id + 1) % param->rules.nbr_phi;
		second_fork = phi->phi_id;
	}
	pthread_mutex_lock(&forks[first_fork].fork_mutex);
	print_log(param, phi->phi_id, "has taken a fork");
	pthread_mutex_lock(&forks[second_fork].fork_mutex);
	print_log(param, phi->phi_id, "has taken a fork");
	pthread_mutex_lock(&param->philos[phi->phi_id].eat_mutex);
	print_log(param, phi->phi_id, "is eating");
	pthread_mutex_lock(&param->philos[phi->phi_id].die_mutex);
	phi->start_time = get_time();
	pthread_mutex_unlock(&param->philos[phi->phi_id].die_mutex);
	usleep(param->rules.t_eat * 1000);
	phi->nbr_eaten++;
	pthread_mutex_unlock(&param->philos[phi->phi_id].eat_mutex);
	pthread_mutex_unlock(&forks[second_fork].fork_mutex);
	pthread_mutex_unlock(&forks[first_fork].fork_mutex);
}

void	*est_actions(void *arg)
{
	t_philo	*phi;
	t_param	*param;

	phi = (t_philo *)arg;
	param = phi->param;
	while (!param->stop)
	{
		if (!phi->is_dead && phi->nbr_eaten < param->rules.nbr_eat)
		{
			if (param->rules.nbr_phi == 1)
			{
				print_log(param, phi->phi_id, "has taken a fork");
				usleep(param->rules.t_die * 1000);
				break ;
			}
			eat(param, phi, param->forks);
			print_log(param, phi->phi_id, "is sleeping");
			usleep(param->rules.t_sleep * 1000);
			print_log(param, phi->phi_id, "is thinking");
		}
	}
	return (NULL);
}
