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
		ft_printf("%d %d %s\n", get_time(), id, status);
	pthread_mutex_unlock(&param->print_mutex);
}

t_fork	*init_forks(int nbr_phi)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * nbr_phi);
	if (!forks)
	{
		ft_printf("Error: Memory allocation failed for forks.\n");
		return (NULL);
	}
	i = 0;
	while (i < nbr_phi)
	{
		forks[i].fork_id = i;
		pthread_mutex_init(&forks[i].fork_mutex, NULL);
		i++;
	}
	return (forks);
}

int	init_param(t_param *param, t_rules rules, t_philo *phi)
{
	param->rules = rules;
	param->philos = phi;
	param->forks = init_forks(rules.nbr_phi);
	if (!param->forks)
		return (-1);
	param->stop = 0;
	pthread_mutex_init(&param->print_mutex, NULL);
	return (0);
}

void	destroy_param(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->rules.nbr_phi)
	{
		pthread_mutex_destroy(&param->philos[i].die_mutex);
		pthread_mutex_destroy(&param->philos[i].eat_mutex);
		pthread_mutex_destroy(&param->philos[i].think_mutex);
		i++;
	}
	pthread_mutex_destroy(&param->print_mutex);
	free(param->forks);
	free(param);
}
