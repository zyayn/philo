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

void	print_log(t_param *param, int id, char *status)
{
	sem_wait(param->print_sem);
	if (!param->stop)
		ft_printf("%d %d %s\n", get_time() - param->begin_time, id, status);
	sem_post(param->print_sem);
}

void	cleanup(t_param *param)
{
	sem_close(param->forks);
	sem_close(param->print_sem);
	sem_unlink("forks");
	sem_unlink("print_sem");
	free(param->philos);
	free(param);
}

void	eat(t_param *param, t_philo *phi)
{
	sem_wait(param->forks);
	print_log(param, phi->phi_id, "has taken a fork");
	sem_wait(param->forks);
	print_log(param, phi->phi_id, "has taken a fork");
	print_log(param, phi->phi_id, "is eating");
	phi->start_time = get_time();
	usleep(param->rules.t_eat * 1000);
	phi->nbr_eaten++;
	sem_post(param->forks);
	sem_post(param->forks);
}

void	est_actions(t_philo *phi)
{
	t_param	*param;

	param = phi->param;
	while (!param->stop && phi->nbr_eaten < param->rules.nbr_eat)
	{
		if (param->rules.nbr_phi == 1)
		{
			print_log(param, phi->phi_id, "has taken a fork");
			usleep(param->rules.t_die * 1000);
			break ;
		}
		eat(param, phi);
		print_log(param, phi->phi_id, "is sleeping");
		usleep(param->rules.t_sleep * 1000);
		print_log(param, phi->phi_id, "is thinking");
	}
	exit(0);
}
