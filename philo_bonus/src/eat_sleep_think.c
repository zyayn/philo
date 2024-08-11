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

#include "philo_bonus.h"

void	check_dead(t_param *param, int id)
{
	int	i;

	if (get_time() - param->philos[id].start_time >= param->rules.t_die)
	{
		print_log(param, id, "died");
		param->stop = 1;
	}
	if (param->stop)
	{
		i = 0;
		while (i < param->rules.nbr_phi)
		{
			kill(param->philos[i].pid, SIGKILL);
			i++;
		}
		exit(1);
	}
}

void	check_all_eaten(t_param *param)
{
	int	phi_full;
	int	i;

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

void	monitor(t_param *param)
{
	int	i;

	while (!param->stop)
	{
		i = 0;
		while (i < param->rules.nbr_phi)
		{
			check_dead(param, i);
			if (param->stop)
				break ;
			i++;
		}
		check_all_eaten(param);
	}
}

int	init_sem(t_param *param, t_rules rules)
{
	sem_close(param->forks);
	sem_close(param->print_sem);
	sem_unlink("forks");
	sem_unlink("print_sem");
	param->forks = sem_open("forks", O_CREAT, 0644, rules.nbr_phi);
	param->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	if (param->forks == SEM_FAILED || param->print_sem == SEM_FAILED)
	{
		sem_close(param->forks);
		sem_close(param->print_sem);
		sem_unlink("forks");
		sem_unlink("print_sem");
		ft_printf("Error: Failed to initialize semaphores.\n");
		return (-1);
	}
	return (0);
}

int	init_param(t_param *param, t_rules rules, t_philo *phi)
{
	param->rules = rules;
	param->philos = phi;
	param->begin_time = get_time();
	param->stop = 0;
	if (init_sem(param, rules) == -1)
		return (-1);
	return (0);
}
