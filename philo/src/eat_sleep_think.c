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

void	cleanup(t_param *param, t_philo *phi)
{
	int	i;

	i = 0;
	while (i < param->rules.nbr_phi)
	{
		pthread_mutex_destroy(&phi[i].die_mutex);
		pthread_mutex_destroy(&phi[i].eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&param->print_mutex);
	free(param->forks);
	free(param);
}

void	check_all_eaten(t_philo *phi)
{
	int	i;
	int	phi_full;

	phi_full = 0;
	i = 0;
	while (i < phi->param->rules.nbr_phi)
	{
		if (phi[i].nbr_eaten >= phi->param->rules.nbr_eat)
			phi_full++;
		i++;
	}
	if (phi_full == phi->param->rules.nbr_phi)
		phi->param->stop = 1;
}

void	monitor(t_philo *phi)
{
	int	i;

	while (!phi->param->stop)
	{
		i = 0;
		while (i < phi->param->rules.nbr_phi)
		{
			pthread_mutex_lock(&phi[i].die_mutex);
			if (!phi->param->stop && get_time() - phi[i].start_eat
				>= phi->param->rules.t_die)
			{
				print_log(phi, "died");
				phi[i].param->stop = 1;
			}
			pthread_mutex_unlock(&phi[i].die_mutex);
			i++;
		}
		check_all_eaten(phi);
	}
}

int	init_param(t_param *param, t_rules rules)
{
	int	i;

	param->rules = rules;
	param->forks = malloc(sizeof(t_fork) * rules.nbr_phi);
	if (!param->forks)
	{
		printf("Error: Memory allocation failed for forks.\n");
		free(param);
		return (-1);
	}
	i = 0;
	while (i < rules.nbr_phi)
	{
		param->forks[i].fork_id = i;
		pthread_mutex_init(&param->forks[i].fork_mutex, NULL);
		i++;
	}
	param->begin_time = get_time();
	param->stop = 0;
	pthread_mutex_init(&param->print_mutex, NULL);
	return (0);
}

int	eat_sleep_think(t_rules rules, t_philo *phi)
{
	int		i;
	t_param	*param;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param || init_param(param, rules) == -1)
		return (-1);
	i = -1;
	while (++i < rules.nbr_phi)
	{
		phi[i].param = param;
		phi[i].start_eat = get_time();
		if (pthread_create(&phi[i].thread_id, NULL,
				est_actions, (void *)&phi[i]))
		{
			printf("Error: Unable to create thread.\n");
			free(param);
			return (-1);
		}
	}
	monitor(phi);
	while (--i >= 0)
		pthread_join(phi[i].thread_id, NULL);
	cleanup(param, phi);
	return (0);
}
