/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:00:37 by zchia             #+#    #+#             */
/*   Updated: 2024/08/04 22:00:37 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static t_philo	*init_phi(t_rules rules)
{
	int		i;
	t_philo	*phi;

	phi = (t_philo *)malloc(sizeof(t_philo) * rules.nbr_phi);
	if (!phi)
	{
		printf("Error: Memory allocation failed for philosophers.\n");
		return (NULL);
	}
	i = 0;
	while (i < rules.nbr_phi)
	{
		phi[i].pid = -1;
		phi[i].phi_id = i;
		phi[i].nbr_eaten = 0;
		phi[i].start_eat = 0;
		phi[i].is_full = 0;
		i++;
	}
	return (phi);
}

void	set_rules(t_rules *rules, char **argv)
{
	rules->nbr_phi = ft_atoi(argv[1]);
	rules->t_die = ft_atoi(argv[2]);
	rules->t_eat = ft_atoi(argv[3]);
	rules->t_sleep = ft_atoi(argv[4]);
	if (argv[5] && ft_isint(argv[5]))
		rules->nbr_eat = ft_atoi(argv[5]);
	else
		rules->nbr_eat = MAX_INT;
}

int	init_rules(t_rules *rules, char **argv)
{
	if (!(ft_isint(argv[1]) && ft_isint(argv[2])
			&& ft_isint(argv[3]) && ft_isint(argv[4])))
		return (-1);
	set_rules(rules, argv);
	if (rules->nbr_phi < 1 || rules->nbr_phi > MAX_PHI || rules->t_die <= 0
		|| rules->t_eat <= 0 || rules->t_sleep <= 0 || rules->nbr_eat < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*phi;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Number of arguments must be either 4 or 5.\n");
		return (1);
	}
	if (init_rules(&rules, argv) == -1)
	{
		printf("Error: Unable to initialise rules!\n");
		return (1);
	}
	phi = init_phi(rules);
	if (!phi)
	{
		printf("Error: Unable to initialise philosophers!\n");
		return (1);
	}
	if (eat_sleep_think(rules, phi) == -1)
		printf("Process error in eat, sleep, think!\n");
	free(phi);
	return (0);
}
