/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:12:10 by zchia             #+#    #+#             */
/*   Updated: 2024/08/05 22:12:10 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_dead(t_param *param, int id)
{
	pthread_mutex_lock(&param->philos[id].die_mutex);
	param->philos[id].t_hungry = get_time() - param->philos[id].start_time;
	if (param->philos[id].t_hungry >= param->rules.t_die
		&& !param->philos[id].is_dead)
	{
		print_log(param, id, "died");
		param->philos[id].is_dead = 1;
		param->stop = 1;
	}
	pthread_mutex_unlock(&param->philos[id].die_mutex);
}

void	check_all_eaten(t_param *param)
{
	int	i;
	int	phi_full;

	phi_full = 0;
	i = 0;
	while (i < param->rules.nbr_phi)
	{
		if (param->philos[i].nbr_eaten >= param->rules.nbr_eat)
			phi_full++;
		i++;
	}
	if (phi_full == param->rules.nbr_phi)
		param->stop = 1;
}

void	eat(t_param *param, t_philo *phi, t_fork *forks)
{
	int	first_fork;
	int	second_fork;

	if (!(phi->phi_id % 2))
	{
		first_fork = phi->right;
		second_fork = phi->left;
	}
	else
	{
		first_fork = phi->left;
		second_fork = phi->right;
	}
	pthread_mutex_lock(&forks[first_fork].fork_mutex);
	print_log(param, phi->phi_id, "has taken a fork");
	pthread_mutex_lock(&forks[second_fork].fork_mutex);
	print_log(param, phi->phi_id, "has taken a fork");
	pthread_mutex_lock(&param->philos[phi->phi_id].eat_mutex);
	print_log(param, phi->phi_id, "is eating");
	usleep(param->rules.t_eat * 1000);
	param->philos[phi->phi_id].start_time = get_time();
	param->philos[phi->phi_id].nbr_eaten++;
	pthread_mutex_unlock(&param->philos[phi->phi_id].eat_mutex);
	pthread_mutex_unlock(&forks[second_fork].fork_mutex);
	pthread_mutex_unlock(&forks[first_fork].fork_mutex);
}

void	*est_actions(void *arg)
{
	t_philo	*phi;
	t_param	*param;
	int		id;

	phi = (t_philo *)arg;
	param = phi->param;
	id = phi->phi_id;
	while (!param->stop)
	{
		check_dead(param, id);
		check_all_eaten(param);
		if (!phi->is_dead && phi->nbr_eaten < param->rules.nbr_eat)
		{
			eat(param, phi, param->forks);
			print_log(param, phi->phi_id, "is sleeping");
			usleep(param->rules.t_sleep * 1000);
			print_log(param, id, "is thinking");
		}
	}
	return (NULL);
}

int	eat_sleep_think(t_rules rules, t_philo *phi)
{
	int		i;
	t_param	*param;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param)
		return (-1);
	if (init_param(param, rules, phi) == -1)
		return (-1);
	i = 0;
	while (i < rules.nbr_phi)
	{
		param->philos[i].param = param;
		param->philos[i].start_time = get_time();
		if (pthread_create(&param->philos[i].thread_id, NULL,
				est_actions, (void *)&param->philos[i]))
		{
			ft_printf("Error: Unable to create thread.\n");
			return (-1);
		}
		i++;
	}
	while (--i >= 0)
		pthread_join(param->philos[i].thread_id, NULL);
	destroy_param(param);
	return (0);
}
