/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:17:51 by gscala            #+#    #+#             */
/*   Updated: 2021/08/02 17:17:54 by gscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	sign;
	int	i;
	int	nums;

	i = 0;
	sign = 1;
	nums = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign = sign * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nums *= 10;
		nums += (str[i] - 48);
		i++;
	}
	if (nums < 0 && nums > -2147483648)
		return (sign > 0 ? -1 : 0);
	nums = nums * sign;
	return (nums);
}
