/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:00:04 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/07 14:26:37 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_atof(const char *str)
{
	double	n;
	int		i;
	int		k;
	int		neg;

	i = 0;
	n = 0;
	k = 0;
	neg = 1;
	if (!str)
		return (0);
	while (ftb_isspace(str[i]))
		i++;
	neg = (str[i] == '-') ? -neg : neg;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	while (str[i] >= 48 && str[i] <= 57)
	{
		n = n * 10 + (str[i++] - 48);
		if (str[i] == '.')
			k = i++;
	}
	while (k != 0 && str[++k])
		neg = neg * 10;
	return (n / neg);
}
