/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:18:54 by benmoham          #+#    #+#             */
/*   Updated: 2022/02/07 18:55:43 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(const char *str)
{
	int i;
	int neg;
	int res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\n' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = neg * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * neg);
}

int	ft_isdigit(char s)
{
	if (s >= '0' && s <= '9')
		return (0);
	else
		return (1);
}

void    check_arg(char **av)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while(av[i])
    {
        while (av[i][j])
        {
            if (ft_isdigit(av[i][j]) == 1 || ft_atoi(av[1]) > 200 || av[i][j] == '-')
            {
                printf("bad character\n");
                exit(1);
            }
            j++;
        }
        j = 0;
        i++;
    }
}