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

void	check_status(t_param *param, t_rules rules)
{
	int	i;

	while (!param->stop)
	{
		i = 0;
		while (i < rules.nbr_phi)
		{
			check_dead(param, i);
			check_all_eaten(param);
			i++;
		}
	}
}

int	init_param(t_param *param, t_rules rules, t_philo *phi)
{
	int	i;

	param->rules = rules;
	param->philos = phi;
	param->forks = malloc(sizeof(t_fork) * rules.nbr_phi);
	if (!param->forks)
	{
		ft_printf("Error: Memory allocation failed for forks.\n");
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
	if (!param || init_param(param, rules, phi) == -1)
		return (-1);
	i = -1;
	while (++i < rules.nbr_phi)
	{
		param->philos[i].param = param;
		param->philos[i].start_time = get_time();
		if (pthread_create(&param->philos[i].thread_id, NULL,
				est_actions, (void *)&param->philos[i]))
		{
			ft_printf("Error: Unable to create thread.\n");
			free(param);
			return (-1);
		}
	}
	check_status(param, rules);
	while (--i >= 0)
		pthread_join(param->philos[i].thread_id, NULL);
	destroy_param(param);
	return (0);
}
